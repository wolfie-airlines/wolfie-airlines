#include "plane.h"

#include <iostream>
#include <unordered_set>

#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../tickets/tickets_prints/tickets_prints.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

void ProcessSeatSelectionAndPurchase(
    std::vector<int> seats_taken,
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user) {
  using namespace ftxui;
  std::string planeId = "WOLFIE PLANE #";
  std::string flight_identifier = found_connection.GetIdentifier();
  for (char c : flight_identifier) {
    if (c != '-') {
      planeId += std::to_string(static_cast<int>(c));
    }
  }

  auto seatStyle = size(WIDTH, EQUAL, 10);

  std::unordered_set<int> seatsTakenSet(seats_taken.begin(), seats_taken.end());

  auto make_seat_box = [&](int seatNumber, bool selected) {
    int rowNumber = (seatNumber % 9 == 0 ? seatNumber / 9 : seatNumber / 9 + 1);
    int seatInRow = (seatNumber % 9 == 0 ? 9 : seatNumber % 9);
    std::string title = " R:" + std::to_string(rowNumber) + " M:" + std::to_string(seatInRow);

    if (selected || seatsTakenSet.count(seatNumber)) {
      auto seatColor = selected ? Color::Orange1 : Color::Red1;
      return window(
          text(title) | hcenter | bold | seatStyle,
          text(selected ? "WYBRANE" : "\u274C") | hcenter | bold | seatStyle | color(seatColor));
    }

    if (seatNumber == 37 || seatNumber == 45) {
      return window(
          text(title) | hcenter | bold | seatStyle,
          text("\U0001f198") | hcenter | bold | color(Color::Orange1) | seatStyle);
    } else {
      return window(
          text(title) | hcenter | bold | seatStyle,
          text("DOSTĘPNE") | hcenter | dim | bold | color(Color::Green) | seatStyle);
    }
  };

  auto style = size(WIDTH, GREATER_THAN, 150) | border;

  std::vector<Element> seats;
  seats.reserve(81);
  Elements document;

  for (int i = 0; i < 81; i++) {
    int seatNumber = i + 1;
    seats.push_back(make_seat_box(seatNumber, false));
  }

  for (size_t i = 0; i < seats.size(); i += 9) {
    Elements row;
    for (size_t j = i; j < i + 9 && j < seats.size(); j++) {
      row.push_back(seats[j]);
      if ((j + 1 - i) % 3 == 0 && j < i + 8) {  // oddziałka co 3 miejsce w kolumnie
        row.push_back(separator());
      }
    }
    document.push_back(hbox(row));
    if (i + 9 < seats.size()) {
      document.push_back(separator());
    }
  }

  auto container = vbox({
                            hbox({text(planeId) | bold}) | color(Color::Blue) | hcenter,
                            separator(),
                            vbox(document) | hcenter,
                            separator(),
                            text("LEGENDA") | ftxui::color(ftxui::Color::BlueLight) | bold | hcenter,
                            ftxui::vbox({
                                            ftxui::hbox({ftxui::text("\U0001f198 "),
                                                         ftxui::text(
                                                             "- miejsce ewakuacyjne (wymagana znajomość angielskiego i brak zastrzeżeń lekarskich)")
                                                             | ftxui::color(ftxui::Color::Orange1)}),
                                            ftxui::hbox({ftxui::text("\u274C "),
                                                         ftxui::text("- zajęte miejsce")
                                                             | ftxui::color(ftxui::Color::Red1) | ftxui::bold}),
                                            ftxui::hbox({ftxui::text("R ") | ftxui::color(ftxui::Color::Grey84)
                                                             | ftxui::bold,
                                                         ftxui::text("- rząd (numer rzędu),")
                                                             | ftxui::color(ftxui::Color::Grey84),
                                                         ftxui::text(" M ") | ftxui::color(ftxui::Color::Grey84)
                                                             | ftxui::bold,
                                                         ftxui::text("- miejsce (numer miejsca)")
                                                             | ftxui::color(ftxui::Color::Grey84)}),
                                        }) | ftxui::hcenter,
                        }) |
      style;

  auto userScreen = Screen::Create(Dimension::Fit(container), Dimension::Fit(container));
  Render(userScreen, container);
  std::cout << userScreen.ToString() << '\0' << std::endl;

  int ticketAmount;
  while (true) {
    std::string ticketAmountInput = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj liczbę biletów (od 1 do 4):");

    if (ticketAmountInput == "back") {
      PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
      return;
    }

    try {
      ticketAmount = std::stoi(ticketAmountInput);
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawna liczba biletów.", "Podaj liczbę biletów od 1 do 4.");
      return;
    }

    if (ticketAmount >= 1 && ticketAmount <= 4) {
      break;
    }
  }

  std::vector<int> selectedSeats;

  for (int i = 0; i < ticketAmount; ++i) {
    std::string rowInput = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj rząd dla biletu " + std::to_string(i + 1) + ":");
    int rowInputNumber;
    try {
      rowInputNumber = std::stoi(rowInput);
      if (rowInputNumber < 1 || rowInputNumber > 9) {
        PrintErrorMessage("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
        return;
      }
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
      return;
    }
    std::string seatInput = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj miejsce dla biletu " + std::to_string(i + 1) + ":");
    int seat;
    try {
      seat = std::stoi(seatInput);
      if (seat < 1 || seat > 9) {
        PrintErrorMessage("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
        return;
      }
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
      return;
    }

    int selectedSeatNumber = (rowInputNumber - 1) * 9 + seat;
    if (std::find(seats_taken.begin(), seats_taken.end(), selectedSeatNumber) != seats_taken.end()) {
      PrintErrorMessage("Miejsce jest już zajęte.", "Wybierz inne miejsce.");
      return;
    }

    selectedSeats.push_back(selectedSeatNumber);
  }

  // aktualizacja zaznaczonych miejsc w samolocie
  for (int selectedSeat : selectedSeats) {
    seats[selectedSeat - 1] = make_seat_box(selectedSeat, true);
  }

  document.clear();
  if (seats.size() >= 9) {
    for (size_t i = 0; i < seats.size(); i += 9) {
      Elements row;
      for (size_t j = i; j < i + 9 && j < seats.size(); j++) {
        row.push_back(seats[j]);
        if ((j + 1 - i) % 3 == 0 && j < i + 8) {  // oddziałka co 3 miejsce w kolumnie
          row.push_back(separator());
        }
      }
      document.push_back(hbox(row));
      if (i + 9 < seats.size()) {
        document.push_back(separator());
      }
    }
  }

  auto containerWithSelectedSeats = vbox({
                                             hbox({text(planeId) | bold}) | color(Color::Blue) | hcenter,
                                             separator(),
                                             vbox(document) | hcenter,
                                             separator(),
                                             text("Czy potwierdzasz wybrane miejsca?") | bold | hcenter,
                                             text("Każdy inny wybór spowoduje anulowanie kupowania biletów.") | bold
                                                 | hcenter,
                                         }) |
      style;

  PrintNodeScreen(containerWithSelectedSeats);

  std::string confirmChoice = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Czy potwierdzasz wybrane miejsca? (tak)");

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
