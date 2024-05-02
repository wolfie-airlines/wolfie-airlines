#include "tickets.h"

#include <random>

#include "../flights/flights_functions/flight_prints/flight_prints.h"
#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../plane/plane.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "tickets_prints/tickets_prints.h"

const int MAX_TICKETS = 4;
const int EMERGENCY_SEAT_ONE = 37;
const int EMERGENCY_SEAT_TWO = 45;

void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user) {
  using namespace ftxui;
  std::string flight_identifier = found_connection.GetIdentifier();
  std::vector<int> seatsTaken = flight_connection.GetSeatsTaken(flight_identifier);
  int ticketAmount;
  while (true) {
    std::string ticketAmountInput = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj liczbę biletów do kupienia (minimalnie 1 do maksymalnie " + std::to_string(MAX_TICKETS) + "):");

    if (ticketAmountInput == "back") {
      PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
      return;
    }

    try {
      ticketAmount = std::stoi(ticketAmountInput);
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawna liczba biletów.", "Podaj liczbę biletów od 1 do " + std::to_string(MAX_TICKETS));
      return;
    }

    if (ticketAmount >= 1 && ticketAmount <= MAX_TICKETS) {
      break;
    }
  }

  std::vector<int> selectedSeats;
  bool hasPrivilege = user.discount_type_ == "ulga";

  for (int i = 0; i < ticketAmount; i++) {
    int seat;
    while (true) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(1, 81);
      seat = dis(gen);
      if (std::find(seatsTaken.begin(), seatsTaken.end(), seat) == seatsTaken.end()) {
        if (hasPrivilege && (seat == EMERGENCY_SEAT_ONE || seat == EMERGENCY_SEAT_TWO)) {
          if (std::count_if(seatsTaken.begin(),
                            seatsTaken.end(),
                            [](int i) { return i != EMERGENCY_SEAT_ONE && i != EMERGENCY_SEAT_TWO; }) == 79) {
            std::string response = DisplayWarningAndCaptureInput("Uwaga!",
                                                                 "Jedynymi dostępnymi miejscami są miejsca awaryjne: "
                                                                     + std::to_string(EMERGENCY_SEAT_ONE) + "i "
                                                                     + std::to_string(EMERGENCY_SEAT_TWO)
                                                                     + ". Czy chcesz kontynuować? (tak/nie)");
            if (response == "tak" || response == "TAK" || response == "Tak") {
              break;
            }
          } else {
            continue;
          }
        } else {
          break;
        }
      }
    }
    selectedSeats.push_back(seat);
  }

  std::string confirmChoice;

  if (ticketAmount == 1) {
    confirmChoice = DisplayMessageAndCaptureStringInput(
        "Potwierdzenie zakupu biletów",
        "Czy na pewno chcesz kupić " + std::to_string(ticketAmount) + " bilet na lot " +
            found_connection.GetIdentifier() + " (tak/nie)");
  } else {
    confirmChoice = DisplayMessageAndCaptureStringInput(
        "Potwierdzenie zakupu biletów",
        "Czy na pewno chcesz kupić " + std::to_string(ticketAmount) + " bilety na lot " +
            found_connection.GetIdentifier() + " (tak/nie)");
  }

  if (confirmChoice != "tak" && confirmChoice != "TAK" && confirmChoice != "Tak") {
    PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
    return;
  }

  std::string titleMessage = "Potwierdzenie zakupu biletów";
  int price = found_connection.GetPrice() * user.discount_ * ticketAmount;
  bool paymentSuccess = AuthenticatePayment(user, user.payment_method_, titleMessage, price);

  if (!paymentSuccess) {
    PrintErrorMessage("Nie udało się przetworzyć płatności.", "Zakup biletów został anulowany.");
    return;
  }

  if (user.discount_ != 1) {
    user.UpdateMoneySaved(found_connection.GetPrice() * ticketAmount, price);
  }

  flight_connection.UpdateSeatsTaken(flight_identifier, selectedSeats);
  user.AddTicketToUser(selectedSeats, found_connection);
  PrintTicketInvoice(user, found_connection, selectedSeats);
}

void HandleFlightById(FlightConnection &flight_connection, User &user) {
  std::string flightId = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj identyfikator lotu:");

  FlightConnection foundConnection = flight_connection.FindConnectionById(flightId);

  if (foundConnection.GetIdentifier() != flightId) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  CreateFoundFlightScreen(foundConnection, user);
  bool validFlightChoice = ValidChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
  if (!validFlightChoice) {
    PrintErrorMessage("Nie wybrano lotu.", "Spróbuj ponownie.");
    return;
  }

  std::vector<int> seatsTaken = flight_connection.GetSeatsTaken(flightId);
  if (seatsTaken.size() == 81) {
    PrintErrorMessage("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
    return;
  }
  std::string premiumCard = user.premium_card_;
  if (premiumCard == "platynowa") {
    ProcessSeatSelectionAndPurchase(seatsTaken, flight_connection, foundConnection, user);
  } else {
    ProcessPurchase(flight_connection, foundConnection, user);
  }
}

void HandleFlightByData(FlightConnection &flight_connection, User &user) {
  std::string departureCity = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj miasto wylotu:");

  std::string arrivalCity = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj miasto przylotu:");

  std::vector<FlightConnection> foundArrivalConnections = flight_connection.FindConnectionsByDestination(arrivalCity);
  std::vector<FlightConnection> foundDepartureConnections = flight_connection.FindConnectionsByDeparture(departureCity);

  if (foundArrivalConnections.empty() || foundDepartureConnections.empty()) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  FlightConnection foundConnection = flight_connection.FindConnection(departureCity, arrivalCity);

  if (foundConnection.GetDepartureCity() != departureCity || foundConnection.GetDestinationCity() != arrivalCity) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  CreateFoundFlightScreen(foundConnection, user);
  bool validFlightChoice = ValidChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
  if (!validFlightChoice) {
    PrintErrorMessage("Nie wybrano lotu.", "Spróbuj ponownie.");
    return;
  }

  std::vector<int> seatsTaken = flight_connection.GetSeatsTaken(foundConnection.GetIdentifier());
  if (seatsTaken.size() == 81) {
    PrintErrorMessage("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
    return;
  }
  std::string premiumCard = user.premium_card_;
  if (premiumCard == "platynowa") {
    ProcessSeatSelectionAndPurchase(seatsTaken, flight_connection, foundConnection, user);
  } else {
    ProcessPurchase(flight_connection, foundConnection, user);
  }
}

void HandleBuyTicket(int choice, FlightConnection &flight_connection, User &user) {
  if (choice == 0) {
    HandleFlightById(flight_connection, user);
  } else if (choice == 1) {
    HandleFlightByData(flight_connection, user);
  }
}

void HandleTicketChoice(FlightConnection &flight_connection, User &user) {
  int choice = CreateTicketMenu();
  HandleBuyTicket(choice, flight_connection, user);
}