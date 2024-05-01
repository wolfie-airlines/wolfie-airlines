#include "checkin_functions_prints.h"
#include "../tickets/user_tickets/user_tickets_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "../functions/info_print_functions.h"
#include "../qr-code/qrcode_prints.h"

const std::string CHECKIN_SCREEN_TITLE = "ODPRAWA BILETOWA";
const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";

std::shared_ptr<ftxui::Element> createScreen(const std::string& message) {
    auto summary = ftxui::vbox({
                                       ftxui::hbox({ftxui::paragraphAlignCenter(CHECKIN_SCREEN_TITLE)}) | color(ftxui::Color::GrayDark),
                                       ftxui::separator(),
                                       ftxui::hbox({ftxui::paragraphAlignRight(message)}) | color(ftxui::Color::LightSteelBlue),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter(AIRPORT_NAME), summary)});
    return std::make_shared<ftxui::Element>(document);
}

void printScreen(const std::shared_ptr<ftxui::Element>& screen) {
    auto finalScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*screen), ftxui::Dimension::Fit(*screen));
    ftxui::Render(finalScreen, *screen);
    std::cout << finalScreen.ToString() << '\0' << std::endl;
}


void createCheckinScreen(User& user) {
    mongocxx::cursor cursor = user.findUserInDatabase(user.getCollection());
    if (cursor.begin() == cursor.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::view userView = *cursor.begin();
    bsoncxx::document::element userFlightsElement = userView["userFlights"];
    bsoncxx::array::view userFlightsArray = userFlightsElement.get_array().value;

    if (userFlightsArray.begin() == userFlightsArray.end()) {
        errorFunction("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
        return;
    }

    // jeśli wszystkie bilety są już odprawione, też nie ma sensu wykonywać tej funkcji
    bool allCheckedIn = true;
    for (const auto &flight: userFlightsArray) {
        if (!flight["checkin"].get_bool().value) {
            allCheckedIn = false;
            break;
        }
    }

    if (allCheckedIn) {
        errorFunction("Nie posiadasz żadnych biletów do odprawienia.", "");
        return;
    }

    std::optional<std::string> option = createTicketsScreen(user, true);
    if(option == "quit") {
        errorFunction("Anulowano odprawę.", "Odprawa biletowa została anulowana. Zawsze możesz wrócić do niej kiedy indziej.");
    } else if (option == "wybieram") {

        auto checkinScreen = createScreen("Podaj NUMER LOTU, na który chciałbyś się odprawić:");
        printScreen(checkinScreen);

        int flightNumber;
        std::cin >> flightNumber;

        if (flightNumber < 1 || flightNumber > userFlightsArray.length()) {
            errorFunction("Nie ma takiego lotu.", "Spróbuj ponownie.");
            return;
        }

        if (userFlightsArray[flightNumber - 1]["checkin"].get_bool().value) {
            errorFunction("Ten lot został już odprawiony.", "Wybierz inny lot.");
            return;
        }

        std::string flightId = (std::string) userFlightsArray[flightNumber - 1]["flightId"].get_string().value;
        std::vector<int> seats;
        for (const auto &seat: userFlightsArray[flightNumber - 1]["seats"].get_array().value) {
            seats.push_back(seat.get_int32().value);
        }

        auto qrInfoScreen = createScreen("Zeskanuj poniższy kod QR żeby się odprawić. Tak! To takie proste!");
        printScreen(qrInfoScreen);

        createQR(user.email, user.username, flightId, seats);
    }
}
