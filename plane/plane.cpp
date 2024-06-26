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
  std::string plane_id = "WOLFIE PLANE #";
  std::string flight_identifier = found_connection.GetIdentifier();
  for (char c : flight_identifier) {
    if (c != '-') {
      plane_id += std::to_string(static_cast<int>(c));
    }
  }

  auto seat_style = size(WIDTH, EQUAL, 10);

  std::unordered_set<int> seats_taken_set(seats_taken.begin(), seats_taken.end());

  auto make_seat_box = [&](int seat_number, bool selected) {
    int row_number = (seat_number % 9 == 0 ? seat_number / 9 : seat_number / 9 + 1);
    int seat_in_row = (seat_number % 9 == 0 ? 9 : seat_number % 9);
    std::string title = " R:" + std::to_string(row_number) + " M:" + std::to_string(seat_in_row);

    if (selected || seats_taken_set.count(seat_number)) {
      auto seatColor = selected ? Color::Orange1 : Color::Red1;
      return window(
          text(title) | hcenter | bold | seat_style,
          text(selected ? "WYBRANE" : "\u274C") | hcenter | bold | seat_style | color(seatColor));
    }

    if (seat_number == 37 || seat_number == 45) {
      return window(
          text(title) | hcenter | bold | seat_style,
          text("\U0001f198") | hcenter | bold | color(Color::Orange1) | seat_style);
    } else {
      return window(
          text(title) | hcenter | bold | seat_style,
          text("DOSTĘPNE") | hcenter | dim | bold | color(Color::Green) | seat_style);
    }
  };

  auto style = size(WIDTH, GREATER_THAN, 150) | border;

  std::vector<Element> seats;
  seats.reserve(81);
  Elements document;

  for (int i = 0; i < 81; i++) {
    int seat_number = i + 1;
    seats.push_back(make_seat_box(seat_number, false));
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

  auto container =
      vbox({
               hbox({
                        text(plane_id) | bold}) | color(Color::Blue) | hcenter,
               separator(),
               vbox(document) | hcenter,
               separator(),
               text("LEGENDA") | ftxui::color(ftxui::Color::BlueLight) | bold | hcenter,
               ftxui::vbox({
                               ftxui::hbox({
                                               ftxui::text("\U0001f198 "),
                                               ftxui::text(
                                                   "- miejsce ewakuacyjne (wymagana znajomość angielskiego i brak zastrzeżeń lekarskich)")
                                                   | ftxui::color(ftxui::Color::Orange1)}),
                               ftxui::hbox({
                                               ftxui::text("\u274C "),
                                               ftxui::text("- zajęte miejsce") | ftxui::color(ftxui::Color::Red1)
                                                   | ftxui::bold}),
                               ftxui::hbox({ftxui::text("R ") | ftxui::color(ftxui::Color::Grey84) | ftxui::bold,
                                            ftxui::text("- rząd (numer rzędu),") | ftxui::color(ftxui::Color::Grey84),
                                            ftxui::text(" M ") | ftxui::color(ftxui::Color::Grey84) | ftxui::bold,
                                            ftxui::text("- miejsce (numer miejsca)")
                                                | ftxui::color(ftxui::Color::Grey84)})})
                   | ftxui::hcenter}) | style;

  auto user_screen = Screen::Create(Dimension::Fit(container), Dimension::Fit(container));
  Render(user_screen, container);
  std::cout << user_screen.ToString() << '\0' << std::endl;

  int ticket_amount;
  while (true) {
    std::string amount_input = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj liczbę biletów (od 1 do 4):");

    if (amount_input == "back") {
      PrintErrorMessage("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
      return;
    }

    try {
      ticket_amount = std::stoi(amount_input);
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawna liczba biletów.", "Podaj liczbę biletów od 1 do 4.");
      return;
    }

    if (ticket_amount >= 1 && ticket_amount <= 4) {
      break;
    }
  }

  std::vector<int> selected_seats;

  for (int i = 0; i < ticket_amount; ++i) {
    std::string row_input = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj rząd dla biletu " + std::to_string(i + 1) + ":");
    int row_input_number;
    try {
      row_input_number = std::stoi(row_input);
      if (row_input_number < 1 || row_input_number > 9) {
        PrintErrorMessage("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
        return;
      }
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
      return;
    }
    std::string seat_input = DisplayMessageAndCaptureStringInput(
        "Zakup biletów",
        "Podaj miejsce dla biletu " + std::to_string(i + 1) + ":");
    int seat;
    try {
      seat = std::stoi(seat_input);
      if (seat < 1 || seat > 9) {
        PrintErrorMessage("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
        return;
      }
    } catch (std::invalid_argument &e) {
      PrintErrorMessage("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
      return;
    }

    int selected_seat_number = (row_input_number - 1) * 9 + seat;
    if (std::find(seats_taken.begin(), seats_taken.end(), selected_seat_number) != seats_taken.end()) {
      PrintErrorMessage("Miejsce jest już zajęte.", "Wybierz inne miejsce.");
      return;
    }

    selected_seats.push_back(selected_seat_number);
  }

  // aktualizacja zaznaczonych miejsc w samolocie
  for (int selectedSeat : selected_seats) {
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

  auto container_with_selected_seats = vbox({
                                             hbox({text(plane_id) | bold}) | color(Color::Blue) | hcenter,
                                             separator(),
                                             vbox(document) | hcenter,
                                             separator(),
                                             text("Czy potwierdzasz wybrane miejsca?") | bold | hcenter,
                                             text("Każdy inny wybór spowoduje anulowanie kupowania biletów.") | bold
                                                 | hcenter,
                                         }) |
      style;

  PrintNodeScreen(container_with_selected_seats);

  std::string confirm_choice = DisplayMessageAndCaptureStringInput(
      "Zakup biletów",
      "Czy potwierdzasz wybrane miejsca? (tak)");

  if (confirm_choice != "tak" && confirm_choice != "TAK" && confirm_choice != "Tak") {
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
