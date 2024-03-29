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
                                           ftxui::hbox({ftxui::text(L"4. Kup bilet na podróż   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
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
                                           ftxui::hbox({ftxui::text(L"4. Kup bilet na podróż   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
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

