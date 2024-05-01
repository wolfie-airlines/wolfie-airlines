#include "user_print_functions.h"

#include <iostream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

std::shared_ptr<ftxui::Element> CreateDefaultMenu() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::text(L"1. Zarejestruj się   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Zaloguj się   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Wyszukaj połączenie   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Kup bilet na podróż   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Odprawy online   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),

            ftxui::hbox({ftxui::text(L"quit. Zamknij aplikację   ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:") | ftxui::bold}) | color(ftxui::Color::YellowLight),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    return std::make_shared<ftxui::Element>(document);
}

std::shared_ptr<ftxui::Element> CreateUserMenu(const User& user) {
    auto summary = [&] {
        std::string usernameAndTitle = user.username;
        if (user.checkIfAdmin()) {
            usernameAndTitle += ", Administrator";
        }

        ftxui::Color usernameColor = ftxui::Color::GrayDark;
        if (user.checkIfAdmin()) {
            usernameColor = ftxui::Color::Gold1;
        }
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::paragraphAlignRight("Zalogowano jako:")}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::paragraphAlignRight(usernameAndTitle)}) | color(usernameColor),
            ftxui::hbox({ftxui::text(L"1. Wyszukaj połączenie   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Kup bilet na podróż   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Zakup kartę premium   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Zarządzaj ulgami   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Moje bilety   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"6. Odprawa biletowa   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"7. Odprawa bagażowa   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"8. Panel administratora   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"profil. Przejdź do swojego profilu   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            ftxui::hbox({ftxui::text(L"settings. Przejdź do ustawień   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            ftxui::hbox({ftxui::text(L"logout. Wyloguj się   ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:") | ftxui::bold}) | color(ftxui::Color::YellowLight),
        });

        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    return std::make_shared<ftxui::Element>(document);
}

std::string CreateSettingsMenu(const User& user) {
    auto createSettingsScreen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" USTAWIENIA KONTA") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::paragraphAlignRight("Zalogowano jako:")}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::paragraphAlignRight(user.username)}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"1. Zmień nazwę użytkownika   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Zmień e-mail   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Zmień hasło   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Zweryfikuj swój zawód   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Zmień domyślną metodę płatności   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"back. \U0001F519 Wróć do głównego menu   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:") | ftxui::bold}) | color(ftxui::Color::YellowLight),
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

int CreateDefaultPaymentScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
        "Zmień domyślną metodę płatności na kartę VISA",
        "Zmień domyślną metodę płatności na BLIK",
        "\U0001F519 Wróć do menu głównego",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

void CreateProfileScreen(User& user) {
    std::string username = user.username;
    std::transform(username.begin(), username.end(), username.begin(), ::toupper);

    std::string profession = user.profession;
    profession[0] = std::toupper(profession[0]);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << user.moneySpent;
    std::string moneySpent = oss.str();
    std::string ticketBought = std::to_string(user.ticketBought);

    std::string premiumCard = user.premiumCard;
    premiumCard[0] = std::toupper(premiumCard[0]);

    std::string paymentMethod = user.paymentMethod;
    paymentMethod[0] = std::toupper(paymentMethod[0]);

    std::string discount = user.recognizeDiscount();

    std::ostringstream oss2;
    oss2 << std::fixed << std::setprecision(2) << user.moneySaved;
    std::string moneySaved = oss2.str();

    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(" PROFIL UŻYTKOWNIKA ") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                         ftxui::text(username) | ftxui::color(ftxui::Color::CadetBlue)}),
            ftxui::hbox({ftxui::text("")}),
            ftxui::hbox({ftxui::text("Wykonywany zawód: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.profession == "brak") ? ftxui::text("Brak") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(profession) | ftxui::color(ftxui::Color::Green)}),
            ftxui::hbox({ftxui::text("Karta premium: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.premiumCard == "brak") ? ftxui::text("Brak") | ftxui::color(ftxui::Color::GrayDark) : (user.premiumCard == "złota")   ? ftxui::text(premiumCard) | ftxui::color(ftxui::Color::Gold1)
                                                                                                                 : (user.premiumCard == "niebieska") ? ftxui::text(premiumCard) | ftxui::color(ftxui::Color::SkyBlue1)
                                                                                                                 : (user.premiumCard == "szara")     ? ftxui::text(premiumCard) | ftxui::color(ftxui::Color::GrayLight)
                                                                                                                 : (user.premiumCard == "platynowa") ? ftxui::text(premiumCard) | ftxui::color(ftxui::Color::LightSteelBlue1)
                                                                                                                                                     : ftxui::text("brak") | ftxui::color(ftxui::Color::GrayDark)}),
            ftxui::hbox({ftxui::text("Zniżka: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (discount == "brak") ? ftxui::text("Brak") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(discount) | ftxui::color(ftxui::Color::SkyBlue2)}),
            ftxui::hbox({ftxui::text("Pieniądze zaoszczędzone dzięki zniżce / karcie premium: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.moneySaved == 0) ? ftxui::text("Brak") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(moneySaved + "zł") | ftxui::color(ftxui::Color::Gold1)}),
            ftxui::hbox({ftxui::text("Data utworzenia konta: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(user.registrationDate) | ftxui::color(ftxui::Color::SteelBlue)}),
            ftxui::hbox({ftxui::text("Domyślna metoda płatności: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(paymentMethod) | ftxui::color(ftxui::Color::Gold1)}),
            ftxui::hbox({ftxui::text("Liczba zakupionych biletów: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(ticketBought) | ftxui::color(ftxui::Color::Violet)}),
            ftxui::hbox({// U0001F4B8 -> 💸
                         ftxui::text(L"Wydanych \U0001F4B8 w WOLFIE AIRLINES: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(moneySpent + "zł") | ftxui::color(ftxui::Color::SandyBrown)}),
            // ---------
            ftxui::separator(),
            ftxui::hbox({// U0001F519 -> 🔙
                         ftxui::text(L"back. \U0001F519  Wróć do głównego menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Dziękujemy za wybór WOLFIE AIRLINES oraz za to, że jesteś z nami 🙏") | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold}),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*std::make_shared<ftxui::Element>(document)));

    ftxui::Render(screen, *std::make_shared<ftxui::Element>(document));

    std::cout << screen.ToString() << '\0' << std::endl;

    std::string backOption;
    std::cin >> backOption;
    if (backOption == "back") {
        return;
    }
}