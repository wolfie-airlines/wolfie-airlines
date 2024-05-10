#include "main_prints.h"

#include <iostream>

#include "../../user/user_functions/user_prints/user_prints.h"

void PrintScreen(const std::shared_ptr<ftxui::Element> &screen) {
    auto final_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(*screen), ftxui::Dimension::Fit(*screen));
    ftxui::Render(final_screen, *screen);
    std::cout << final_screen.ToString() << '\0' << std::endl;
}

void PrintFullWidthScreen(std::shared_ptr<ftxui::Node> container) {
    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(container));
    ftxui::Render(user_screen, container);
    std::cout << user_screen.ToString() << '\0' << std::endl;
}

void PrintNodeScreen(std::shared_ptr<ftxui::Node> container) {
    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(container), ftxui::Dimension::Fit(container));
    ftxui::Render(user_screen, container);
    std::cout << user_screen.ToString() << '\0' << std::endl;
}

std::string DisplayMessageAndCaptureStringInput(const std::string &title_message, const std::string &text_message) {
    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::White),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(text_message) | ftxui::bold | color(ftxui::Color::GrayLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to the main menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    std::string answer;
    std::cin >> answer;

    return answer;
}

double DisplayMessageAndCaptureDoubleInput(const std::string &title_message, const std::string &text_message) {
    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::White),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(text_message) | ftxui::bold | color(ftxui::Color::GrayLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to the main menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    double answer;
    std::cin >> answer;

    return answer;
}

std::string DisplayWarningAndCaptureInput(const std::string &title_message, const std::string &text_message) {
    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::Red),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(text_message) | ftxui::bold | color(ftxui::Color::RedLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to the main menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    std::string answer;
    std::cin >> answer;

    return answer;
}

void DisplayUserMenu(User &user) {
    auto summary = [&] {
        std::string username_and_title = user.username_;
        if (user.CheckIfAdmin()) {
            username_and_title += ", Administrator";
        }

        ftxui::Color username_color = ftxui::Color::GrayDark;
        if (user.CheckIfAdmin()) {
            username_color = ftxui::Color::Gold1;
        }
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" USER MENU") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::paragraphAlignRight("Logged in as:")}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::paragraphAlignRight(username_and_title)}) | color(username_color),
            ftxui::hbox({ftxui::text(L"1. Search for a connection   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Buy tickets  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Buy premium card   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Manage your discounts   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. My tickets   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"6. Ticket check-in   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"7. Baggage check-in   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"8. Admin panel   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"profil. Go to your profile   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            ftxui::hbox({ftxui::text(L"settings. Go to settings   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            ftxui::hbox({ftxui::text(L"logout. Logout  ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(
                             L"Enter the action (or its number) you want to perform below:") |
                         ftxui::bold}) |
                color(ftxui::Color::YellowLight),
        });

        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto
        user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
    ftxui::Render(user_screen, document);
    std::cout << user_screen.ToString() << '\0' << std::endl;
}

void DisplayMenu() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" USER MENU") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::text(L"1. Register   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Login   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Search for a connection   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Buy tickets   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Check-in online   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),

            ftxui::hbox({ftxui::text(L"quit. Close the application   ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(
                             L"Enter the action (or its number) you want to perform below:") |
                         ftxui::bold}) |
                color(ftxui::Color::YellowLight),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    std::cout << screen.ToString() << '\0' << std::endl;
}