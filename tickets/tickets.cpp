#include "tickets.h"

#include <random>

#include "../flights/flights_functions/flight_prints/flight_prints.h"
#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../plane/plane.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "tickets_prints/tickets_prints.h"

void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user) {
  using namespace ftxui;
  std::string flight_identifier = found_connection.GetIdentifier();
  std::vector<int> seats_taken = flight_connection.GetSeatsTaken(flight_identifier);
  int ticket_amount;
  while (true) {
    std::string amount_input = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj liczbę biletów do kupienia (minimalnie 1 do maksymalnie " + std::to_string(MAX_TICKETS) + "):");

    if (amount_input == "back") {
      PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
      return;
    }

    try {
      ticket_amount = std::stoi(amount_input);
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawna liczba biletów.", "Podaj liczbę biletów od 1 do " + std::to_string(MAX_TICKETS));
      return;
    }

    if (ticket_amount >= 1 && ticket_amount <= MAX_TICKETS) {
      break;
    }
  }

  std::vector<int> selected_seats;
  bool has_privilege = user.discount_type_ == "ulga";

  for (int i = 0; i < ticket_amount; i++) {
    int seat;
    while (true) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(1, 81);
      seat = dis(gen);
      if (std::find(seats_taken.begin(), seats_taken.end(), seat) == seats_taken.end()) {
        if (has_privilege && (seat == EMERGENCY_SEAT_ONE || seat == EMERGENCY_SEAT_TWO)) {
          if (std::count_if(seats_taken.begin(),
                            seats_taken.end(),
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
    selected_seats.push_back(seat);
  }

  std::string choice;

  if (ticket_amount == 1) {
    choice = DisplayMessageAndCaptureStringInput(
        "Potwierdzenie zakupu biletów",
        "Czy na pewno chcesz kupić " + std::to_string(ticket_amount) + " bilet na lot " +
            found_connection.GetIdentifier() + " (tak/nie)");
  } else {
    choice = DisplayMessageAndCaptureStringInput(
        "Potwierdzenie zakupu biletów",
        "Czy na pewno chcesz kupić " + std::to_string(ticket_amount) + " bilety na lot " +
            found_connection.GetIdentifier() + " (tak/nie)");
  }

  if (choice != "tak" && choice != "TAK" && choice != "Tak") {
    PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
    return;
  }

  std::string title_message = "Potwierdzenie zakupu biletów";
  int price = found_connection.GetPrice() * user.discount_ * ticket_amount;
  bool authenticate_payment = AuthenticatePayment(user, user.payment_method_, title_message, price);

  if (!authenticate_payment) {
    PrintErrorMessage("Nie udało się przetworzyć płatności.", "Zakup biletów został anulowany.");
    return;
  }

  if (user.discount_ != 1) {
    user.UpdateMoneySaved(found_connection.GetPrice() * ticket_amount, price);
  }

  flight_connection.UpdateSeatsTaken(flight_identifier, selected_seats);
  user.AddTicketToUser(selected_seats, found_connection);
  PrintTicketInvoice(user, found_connection, selected_seats);
}

void HandleFlightById(FlightConnection &flight_connection, User &user) {
  std::string flight_id = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj identyfikator lotu:");

  FlightConnection found_connection = flight_connection.FindConnectionById(flight_id);

  if (found_connection.GetIdentifier() != flight_id) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  CreateFoundFlightScreen(found_connection, user);
  bool choice = ValidChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
  if (!choice) {
    PrintErrorMessage("Nie wybrano lotu.", "Spróbuj ponownie.");
    return;
  }

  std::vector<int> seats_taken = flight_connection.GetSeatsTaken(flight_id);
  if (seats_taken.size() == 81) {
    PrintErrorMessage("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
    return;
  }
  std::string premium_card = user.premium_card_;
  if (premium_card == "platynowa") {
    ProcessSeatSelectionAndPurchase(seats_taken, flight_connection, found_connection, user);
  } else {
    ProcessPurchase(flight_connection, found_connection, user);
  }
}

void HandleFlightByData(FlightConnection &flight_connection, User &user) {
  std::string departure_city = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj miasto wylotu:");

  std::string arrival_city = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Podaj miasto przylotu:");

  std::vector<FlightConnection> found_arrival_connections = flight_connection.FindConnectionsByDestination(arrival_city);
  std::vector<FlightConnection> found_departure_connections = flight_connection.FindConnectionsByDeparture(departure_city);

  if (found_arrival_connections.empty() || found_departure_connections.empty()) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  FlightConnection found_connection = flight_connection.FindConnection(departure_city, arrival_city);

  if (found_connection.GetDepartureCity() != departure_city || found_connection.GetDestinationCity() != arrival_city) {
    PrintErrorMessage("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
    return;
  }

  CreateFoundFlightScreen(found_connection, user);
  bool choice = ValidChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
  if (!choice) {
    PrintErrorMessage("Nie wybrano lotu.", "Spróbuj ponownie.");
    return;
  }

  std::vector<int> seats_taken = flight_connection.GetSeatsTaken(found_connection.GetIdentifier());
  if (seats_taken.size() == 81) {
    PrintErrorMessage("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
    return;
  }
  std::string premium_card = user.premium_card_;
  if (premium_card == "platynowa") {
    ProcessSeatSelectionAndPurchase(seats_taken, flight_connection, found_connection, user);
  } else {
    ProcessPurchase(flight_connection, found_connection, user);
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