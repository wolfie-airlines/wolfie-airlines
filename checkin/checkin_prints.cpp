#include "checkin_prints.h"

#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../qr_code/qrcode_prints.h"
#include "../user/user_functions/user_tickets/user_tickets_prints.h"
#include "ftxui/dom/elements.hpp"

const std::string CHECKIN_SCREEN_TITLE = "ODPRAWA BILETOWA";
const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";

std::shared_ptr<ftxui::Element> CreateCheckinScreen(const std::string &message) {
  auto summary = ftxui::vbox({
                                 ftxui::hbox({ftxui::paragraphAlignCenter(CHECKIN_SCREEN_TITLE)})
                                     | color(ftxui::Color::GrayDark),
                                 ftxui::separator(),
                                 ftxui::hbox({ftxui::paragraphAlignRight(message)})
                                     | color(ftxui::Color::LightSteelBlue),
                             });
  auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter(AIRPORT_NAME), summary)});
  return std::make_shared<ftxui::Element>(document);
}

void PrintCheckinScreen(User &user) {
  mongocxx::cursor cursor = user.FindUserInDatabase();
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie znaleziono użytkownika w bazie danych.", "Zaloguj się ponownie.");
    return;
  }

  bsoncxx::document::view user_view = *cursor.begin();
  bsoncxx::document::element user_flights_element = user_view["userFlights"];
  bsoncxx::array::view user_flights = user_flights_element.get_array().value;

  if (user_flights.begin() == user_flights.end()) {
    PrintErrorMessage("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
    return;
  }

  // jeśli wszystkie bilety są już odprawione, też nie ma sensu wykonywać tej funkcji
  bool all_checked_in = true;
  for (const auto &flight : user_flights) {
    if (!flight["checkin"].get_bool().value) {
      all_checked_in = false;
      break;
    }
  }

  if (all_checked_in) {
    PrintErrorMessage("Nie posiadasz żadnych biletów do odprawienia.", "");
    return;
  }

  std::optional<std::string> option = CreateTicketsScreen(user, true);
  if (option == "quit") {
    PrintErrorMessage("Anulowano odprawę.",
                      "Odprawa biletowa została anulowana. Zawsze możesz wrócić do niej kiedy indziej.");
  } else if (option == "wybieram") {
    auto checkin_screen = CreateCheckinScreen("Podaj NUMER LOTU, na który chciałbyś się odprawić:");
    PrintScreen(checkin_screen);

    int flight_number;
    std::cin >> flight_number;

    if (flight_number < 1 || flight_number > user_flights.length()) {
      PrintErrorMessage("Nie ma takiego lotu.", "Spróbuj ponownie.");
      return;
    }

    if (user_flights[flight_number - 1]["checkin"].get_bool().value) {
      PrintErrorMessage("Ten lot został już odprawiony.", "Wybierz inny lot.");
      return;
    }

    std::string flightId = (std::string) user_flights[flight_number - 1]["flightId"].get_string().value;
    std::vector<int> seats;
    for (const auto &seat : user_flights[flight_number - 1]["seats"].get_array().value) {
      seats.push_back(seat.get_int32().value);
    }

    auto qr_info_screen = CreateCheckinScreen("Zeskanuj poniższy kod QR żeby się odprawić. Tak! To takie proste!");
    PrintScreen(qr_info_screen);

    CreateQr(user.email_, user.username_, flightId, seats);
  }
}
