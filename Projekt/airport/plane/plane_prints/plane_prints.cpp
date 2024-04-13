#include "plane_prints.h"
#include <iostream>
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/screen_interactive.hpp"


void testPrint(std::vector<int> seatsTaken) {
    using namespace ftxui;

    auto seatStyle = size(WIDTH, EQUAL, 10);

    auto make_seat_box = [&](int seatNumber) {
        int rowNumber = (seatNumber % 9 == 0 ? seatNumber / 9 : seatNumber / 9 + 1);
        int seatInRow = (seatNumber % 9 == 0 ? 9 : seatNumber % 9);
        std::string title = " R:" + std::to_string(rowNumber) + " M:" + std::to_string(seatInRow);

        if (seatNumber == 37 || seatNumber == 45) {
            return window(
                    text(title) | hcenter | bold | seatStyle,
                    text("\U0001f198") | hcenter | bold | color(Color::Orange1) | seatStyle
            );
        } else if (std::find(seatsTaken.begin(), seatsTaken.end(), seatNumber) != seatsTaken.end()) {
            return window(
                    text(title) | hcenter | bold | seatStyle,
                    text("\u274C") | hcenter | dim | color(Color::Red) | seatStyle
            );
        } else {
            return window(
                    text(title) | hcenter | bold | seatStyle,
                    text("DOSTĘPNE") | hcenter | dim | bold | color(Color::Green) | seatStyle
            );
        }
    };

    auto style = size(WIDTH, GREATER_THAN, 150) | border;

    std::vector<Element> seats;
    Elements document;

    for (int i = 0; i < 81; i++) {
        int seatNumber = i + 1;
        seats.push_back(make_seat_box(seatNumber));

        if ((i + 1) % 9 == 0) {
            if ((i + 1) / 9 % 3 != 0) {
                seats.push_back(separator());
            }
            document.push_back(hbox({
                                            seats[0], seats[1], seats[2], separator(),
                                            seats[3], seats[4], seats[5], separator(),
                                            seats[6], seats[7], seats[8]
                                    }));
            seats.clear();
        }
    }

    auto container = vbox({
                                  hbox({
                                               text(L" MENU MIEJSC W SAMOLOCIE") | bold}) | color(Color::Blue) | hcenter,
                                  separator(),
                                  vbox(document) | hcenter,
                                  separator(),
                                  text(" ") | bold | hcenter,
                                  text("To wszystkie miejsca w samolocie.") | bold | hcenter,
                          }) | style;

    auto userScreen = Screen::Create(Dimension::Fit(container), Dimension::Fit(container));
    Render(userScreen, container);
    std::cout << userScreen.ToString() << '\0' << std::endl;
}