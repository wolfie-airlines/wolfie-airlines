#include <iostream>
#include "user_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

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
