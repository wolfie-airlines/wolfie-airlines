#include "admin_prints.h"

#include <iostream>

#include "ftxui/dom/elements.hpp"

void DisplayAdminMenu() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" ADMIN PANEL") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::text(L"1. Add new flight   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Add new verification question   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Manage users   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Add new item  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"quit. Exit the admin dashboard   ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
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

void DisplayAddingFlightInfo() {
    auto summary = [&] {
        auto content = ftxui::vbox({ftxui::hbox({ftxui::text(L"ATTENTION ADMINISTRATOR!") | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                    ftxui::hbox({ftxui::text(L"Adding flight is quite a tale.") | ftxui::bold}) | color(ftxui::Color::Orange3),
                                    ftxui::hbox({ftxui::text(
                                                     L"You must provide all the necessary information for the flight to be added.") |
                                                 ftxui::bold}) |
                                        color(ftxui::Color::Orange1),
                                    ftxui::vbox({
                                        ftxui::hbox({ftxui::text(L"INFORMATION NEEDED:") | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                        ftxui::hbox({
                                            ftxui::text(L"- FLIGHT ID ") | ftxui::bold | color(ftxui::Color::YellowLight),
                                            ftxui::paragraph(
                                                "(Unique flight ID): the naming convention is: FIRST TWO LETTERS OF THE CITY OF DEPARTURE - FIRST TWO LETTERS OF THE CITY OF ARRIVAL)") |
                                                ftxui::bold | color(ftxui::Color::Yellow2),
                                            ftxui::text(
                                                " For example, a flight from Warsaw to Krakow has the ID WA-KR") |
                                                ftxui::bold | color(ftxui::Color::SkyBlue1),
                                        }),
                                        ftxui::hbox({ftxui::text(L"- Departure City") | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                        ftxui::hbox({ftxui::text(
                                                         L"- Destination City") |
                                                     ftxui::bold}) |
                                            color(ftxui::Color::YellowLight),
                                        ftxui::hbox({ftxui::text(
                                                         L"- Departure time ") |
                                                         color(ftxui::Color::YellowLight),
                                                     ftxui::text(
                                                         L"(format: DD.MM.YYYY HH:MM)") |
                                                         color(ftxui::Color::Yellow2) | ftxui::bold}),
                                        ftxui::hbox({ftxui::text(
                                                         L"- Arrival time ") |
                                                         color(ftxui::Color::YellowLight),
                                                     ftxui::text(
                                                         L"(format: DD.MM.YYYY HH:MM)") |
                                                         color(ftxui::Color::Yellow2) | ftxui::bold}),
                                        ftxui::hbox({ftxui::text(L"- Flight price ") | color(ftxui::Color::YellowLight),
                                                     ftxui::text(L"(w PLN)") | color(ftxui::Color::Yellow2) | ftxui::bold}),
                                    }) | ftxui::border,
                                    ftxui::separator(),
                                    ftxui::hbox({ftxui::text(L"If you want to stop adding a flight type:") | ftxui::bold}) | color(ftxui::Color::RedLight),
                                    ftxui::hbox({ftxui::text(L"quit") | ftxui::bold}) | color(ftxui::Color::Red1),
                                    ftxui::separator(),
                                    ftxui::hbox({ftxui::text(L"If you want to continue adding a flight type:") | ftxui::bold}) | color(ftxui::Color::GreenLight),
                                    ftxui::hbox({ftxui::text(L"next") | ftxui::bold}) | color(ftxui::Color::Green1)});
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 120);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    std::cout << screen.ToString() << '\0' << std::endl;
}

std::string DisplayAdminMessageAndCaptureInput(const std::string &title_message, const std::string &text_message) {
    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::White),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(text_message) | ftxui::bold | color(ftxui::Color::GrayLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to admin panel.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
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

std::string DisplayAdminMessageAndCaptureLine(const std::string &title_message, const std::string &text_message) {
    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::White),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(text_message) | ftxui::bold | color(ftxui::Color::GrayLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to admin panel.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    std::string answer;
    std::getline(std::cin >> std::ws, answer);

    return answer;
}

void DisplayManageUsersMenu() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" USER MANAGMENT") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::text(L"1. Change the username of the selected user  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Change the email address of the selected user   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Change the profession of the selected user   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Change the premium card of the selected user  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Change the discount type of the selected user  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"6. Change the discount of the selected user (discount value)  ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"quit. Return to admin panel  ") | ftxui::bold}) | color(ftxui::Color::DarkRed),
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
