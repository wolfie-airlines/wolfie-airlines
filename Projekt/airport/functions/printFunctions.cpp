#include <iostream>
#include "printFunctions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

void validFunction(const std::string& titleMessage, const std::string& optionalMessage="") {
    ftxui::Element response;
    if(optionalMessage.empty()) {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Green),
                               });
    } else {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Green),
                                       ftxui::hbox({ftxui::text(optionalMessage) | ftxui::bold}) | color(ftxui::Color::CyanLight),
                               });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void logoutFunction() {
    ftxui::Element response;
    response = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"Wylogowano pomyślnie. Mamy nadzieję, że do zobaczenia niebawem!") | ftxui::bold}) | color(ftxui::Color::MagentaLight),
                           });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void seeyaFunction() {
    ftxui::Element response;
    response = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"Dziękujemy za skorzystanie z naszych usłuch, mamy nadzieję, że się podobało!") | ftxui::bold}) | color(ftxui::Color::MagentaLight),
                           });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void errorFunction(const std::string& titleMessage, const std::string& optionalMessage="") {
    ftxui::Element response;
    if(optionalMessage.empty()) {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Red),
                               });
    } else {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Red),
                                       ftxui::hbox({ftxui::text(optionalMessage) | ftxui::bold}) | color(ftxui::Color::Orange1),
                               });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

std::shared_ptr<ftxui::Element> CreateScreen() {
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold}) | color(ftxui::Color::Blue),
                                           ftxui::hbox({ftxui::text(L"1. Zarejestruj się   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"2. Zaloguj się   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"3. Wyszukaj połączenie   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"quit. Zamknij aplikację   ")  | ftxui::bold}) | color(ftxui::Color::DarkRed),
                                           // ---------
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:")  | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    return std::make_shared<ftxui::Element>(document);
}

std::shared_ptr<ftxui::Element> CreateUserScreen(const User& user) {
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold}) | color(ftxui::Color::Blue),
                                           ftxui::hbox({ftxui::paragraphAlignRight("Zalogowano jako:")}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::paragraphAlignRight(user.getUsername())}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"1. Zarejestruj się   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"2. Zaloguj się   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"3. Wyszukaj połączenie   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"logout. Wyloguj się   ")  | ftxui::bold}) | color(ftxui::Color::DarkRed),
                                           // ---------
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:")  | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    return std::make_shared<ftxui::Element>(document);
}

std::shared_ptr<ftxui::Element> CreateFlightsScreen(const std::vector<FlightConnection>& connections) {
    auto make_box = [](const std::string &title, int dimx, int dimy, const std::string &content) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::text(content) | ftxui::hcenter | ftxui::dim) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto style = size(ftxui::WIDTH, ftxui::GREATER_THAN, 150) | ftxui::border |
                 size(ftxui::HEIGHT, ftxui::GREATER_THAN, 150);

    std::vector<ftxui::Element> boxes;
    std::cout << connections.size() << std::endl;

    ftxui::Elements document;

    for (int i=0; i < 10; i++) {
        document.push_back(ftxui::hbox({
            make_box("ID LOTU", 25, 5, connections[i].getIdentifier()),
            make_box("CZAS WYLOTU", 50, 5, connections[i].getDepartureTime()),
            make_box("MIEJSCE WYLOTU", 50, 5, connections[i].getDepartureCity()),
            make_box("MIEJSCE PRZYLOTU", 50, 5, connections[i].getDestinationCity()),
            make_box("GODZINA PRZYLOTU", 50, 5, connections[i].getArrivalTime()),
            make_box("CENA", 25, 5, std::to_string((int) connections[i].getPrice()) + " PLN"),
            }));
        }

        auto container = ftxui::vbox({
            ftxui::hbox({
                ftxui::text(L" MENU POŁĄCZEŃ") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter ,
            ftxui::separator(),
            ftxui::vbox(document),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Strona 1/4") | ftxui::bold}) | color(ftxui::Color::YellowLight) | ftxui::hcenter ,
            ftxui::hbox({ftxui::text(L"Przełączaj się między stronami wpisując 1-4") | ftxui::bold}) | color(ftxui::Color::YellowLight) | ftxui::hcenter ,
        }) | style;
        return std::make_shared<ftxui::Element>(container);
    }

