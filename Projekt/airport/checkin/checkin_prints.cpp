#include "checkin_prints.h"

#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../qr-code/qrcode_prints.h"
#include "../user/user_functions/user_tickets/user_tickets_prints.h"
#include "ftxui/dom/elements.hpp"

const std::string CHECKIN_SCREEN_TITLE = "ODPRAWA BILETOWA";
const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";

std::shared_ptr<ftxui::Element> createCheckinScreen(const std::string &message) {
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
  mongocxx::cursor cursor = user.findUserInDatabase();
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie znaleziono użytkownika w bazie danych.", "Zaloguj się ponownie.");
    return;
  }

  bsoncxx::document::view userView = *cursor.begin();
  bsoncxx::document::element userFlightsElement = userView["user_flights_"];
  bsoncxx::array::view userFlightsArray = userFlightsElement.get_array().value;

  if (userFlightsArray.begin() == userFlightsArray.end()) {
    PrintErrorMessage("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
    return;
  }

  // jeśli wszystkie bilety są już odprawione, też nie ma sensu wykonywać tej funkcji
  bool allCheckedIn = true;
  for (const auto &flight : userFlightsArray) {
    if (!flight["checkin"].get_bool().value) {
      allCheckedIn = false;
      break;
    }
  }

  if (allCheckedIn) {
    PrintErrorMessage("Nie posiadasz żadnych biletów do odprawienia.", "");
    return;
  }

  std::optional<std::string> option = createTicketsScreen(user, true);
  if (option == "quit") {
    PrintErrorMessage("Anulowano odprawę.",
                      "Odprawa biletowa została anulowana. Zawsze możesz wrócić do niej kiedy indziej.");
  } else if (option == "wybieram") {
    auto checkinScreen = createCheckinScreen("Podaj NUMER LOTU, na który chciałbyś się odprawić:");
    PrintScreen(checkinScreen);

    int flightNumber;
    std::cin >> flightNumber;

    if (flightNumber < 1 || flightNumber > userFlightsArray.length()) {
      PrintErrorMessage("Nie ma takiego lotu.", "Spróbuj ponownie.");
      return;
    }

    if (userFlightsArray[flightNumber - 1]["checkin"].get_bool().value) {
      PrintErrorMessage("Ten lot został już odprawiony.", "Wybierz inny lot.");
      return;
    }

    std::string flightId = (std::string) userFlightsArray[flightNumber - 1]["flight_id"].get_string().value;
    std::vector<int> seats;
    for (const auto &seat : userFlightsArray[flightNumber - 1]["seats"].get_array().value) {
      seats.push_back(seat.get_int32().value);
    }

    auto qrInfoScreen = createCheckinScreen("Zeskanuj poniższy kod QR żeby się odprawić. Tak! To takie proste!");
    PrintScreen(qrInfoScreen);

    CreateQr(user.email_, user.username_, flightId, seats);
  }
}
