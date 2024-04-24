#include "checkin_functions_prints.h"
#include "../tickets/user_tickets/user_tickets_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "../functions/info_print_functions.h"
#include "../qr-code/qrcode_prints.h"

void createCheckinScreen(User& user) {

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", user.email),
            bsoncxx::builder::basic::kvp("password", user.getPassword())
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = user.getCollection().find(filter_view);
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

    createTicketsScreen(user);
    auto checkinScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter("ODPRAWA BILETOWA")}) | color(ftxui::Color::GrayDark),
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::paragraphAlignRight("Podaj NUMER LOTU, na który chciałbyś się odprawić:")}) | color(ftxui::Color::LightSteelBlue),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        return std::make_shared<ftxui::Element>(document);
    };

    auto finalCheckinScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*checkinScreen()), ftxui::Dimension::Fit(*checkinScreen()));
    ftxui::Render(finalCheckinScreen, *checkinScreen());
    std::cout << finalCheckinScreen.ToString() << '\0' << std::endl;

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

    auto qrInfoScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter("ODPRAWA BILETOWA")}) | color(ftxui::Color::GrayDark),
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::paragraphAlignRight("Zeskanuj poniższy kod QR żeby się odprawić. Tak! To takie proste!")}) | color(ftxui::Color::LightSteelBlue),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        return std::make_shared<ftxui::Element>(document);
    };

    auto qrScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*qrInfoScreen()), ftxui::Dimension::Fit(*qrInfoScreen()));
    ftxui::Render(qrScreen, *qrInfoScreen());
    std::cout << qrScreen.ToString() << '\0' << std::endl;

    createQR(user.email, user.username, flightId, seats);

}
