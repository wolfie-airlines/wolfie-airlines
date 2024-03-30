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
                                           ftxui::hbox({ftxui::text(L"settings. Przejdź do ustawień   ")  | ftxui::bold}) | color(ftxui::Color::CadetBlue),
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

std::string handleSettingsMenu(const User& user) {
    auto createSettingsScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L" USTAWIENIA KONTA") | ftxui::bold}) | color(ftxui::Color::Blue),
                                           ftxui::hbox({ftxui::paragraphAlignRight("Zalogowano jako:")}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::paragraphAlignRight(user.getUsername())}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"1. Zmień nazwę użytkownika   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"2. Zmień e-mail   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"3. Zmień hasło   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"4. Zarządzaj ulgami   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"5. Zweryfikuj swój zawód   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"5. Zmień domyślną metodę płatności   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"back. Wróć do głównego menu   ")  | ftxui::bold}) | color(ftxui::Color::CadetBlue),
                                           // ---------
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:")  | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createSettingsScreen()));
    ftxui::Render(userScreen, *createSettingsScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string option;
    std::cin >> option;
    return option;
}