#include "plane_prints.h"
#include <iostream>
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/screen_interactive.hpp"


void testPrint(std::vector<int> seatsTaken) {
    using namespace ftxui;

    auto seatStyle = size(WIDTH, EQUAL, 10);

    auto make_seat_box = [&](int seatNumber, bool selected) {
        int rowNumber = (seatNumber % 9 == 0 ? seatNumber / 9 : seatNumber / 9 + 1);
        int seatInRow = (seatNumber % 9 == 0 ? 9 : seatNumber % 9);
        std::string title = " R:" + std::to_string(rowNumber) + " M:" + std::to_string(seatInRow);

        if (selected) {
            return window(
                    text(title) | hcenter | bold | seatStyle,
                    text("WYBRANE") | hcenter | bold | color(Color::Orange1) | seatStyle
            );
        }

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
        seats.push_back(make_seat_box(seatNumber, false));
    }

    for (size_t i = 0; i < seats.size(); i += 9) {
        Elements row;
        for (size_t j = i; j < i + 9 && j < seats.size(); j++) {
            row.push_back(seats[j]);
            if ((j + 1 - i) % 3 == 0 && j < i + 8) { // oddziałka co 3 miejsce w kolumnie
                row.push_back(separator());
            }
        }
        document.push_back(hbox(row));
        if (i + 9 < seats.size()) {
            document.push_back(separator());
        }
    }

    auto container = vbox({
                                  hbox({
                                               text(L" MENU MIEJSC W SAMOLOCIE") | bold}) | color(Color::Blue) | hcenter,
                                  separator(),
                                  vbox(document) | hcenter,
                                  separator(),
                                  text("LEGENDA") | bold | hcenter,
                                  ftxui::vbox({
                                                      ftxui::hbox({
                                                                          ftxui::text("\U0001f198 ") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                                                                          ftxui::text("- miejsce ewakuacyjne (wymagana znajomość angielskiego i brak zastrzeżeń lekarskich)") | ftxui::color(ftxui::Color::CadetBlue)
                                                                  }),
                                                      ftxui::hbox({
                                                                          ftxui::text("\u274C ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                                                                          ftxui::text("- zajęte miejsce")
                                                                  }),
                                                      ftxui::hbox({
                                                                          ftxui::text("R ") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                                                                          ftxui::text("- rząd (numer rzędu)") | ftxui::color(ftxui::Color::CadetBlue)
                                                                  }),
                                                      ftxui::hbox({
                                                                          ftxui::text("M ") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                                                                          ftxui::text("- miejsce (numer miejsca)") | ftxui::color(ftxui::Color::CadetBlue)
                                                                  })
                                                }) | ftxui::color(ftxui::Color::GrayDark) | ftxui::hcenter,
                          }) | style;

    auto userScreen = Screen::Create(Dimension::Fit(container), Dimension::Fit(container));
    Render(userScreen, container);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    int ticketAmount = 0;
    while (ticketAmount < 1 || ticketAmount > 4) {
        std::cout << "Podaj liczbę biletów do kupienia (od 1 do 4): ";
        std::cin >> ticketAmount;
    }

    std::vector<int> selectedSeats;

    for (int i = 0; i < ticketAmount; ++i) {
        std::string rowInput;
        std::cout << "Podaj rząd dla biletu " << i + 1 << ": ";
        std::cin >> rowInput;
        int rowInputNumber = std::stoi(rowInput);
        std::string seatInput;
        std::cout << "Podaj miejsce dla biletu " << i + 1 << ": ";
        std::cin >> seatInput;
        int seat = std::stoi(seatInput);
        int selectedSeatNumber = (rowInputNumber - 1) * 9 + seat;

        selectedSeats.push_back(selectedSeatNumber);
    }

    // aktualizacja zaznaczonych miejsc w samolocie
    for (size_t i = 0; i < selectedSeats.size(); ++i) {
        seats[selectedSeats[i] - 1] = make_seat_box(selectedSeats[i], true);
    }

    document.clear();
    if (seats.size() >= 9) {
        for (size_t i = 0; i < seats.size(); i += 9) {
            Elements row;
            for (size_t j = i; j < i + 9 && j < seats.size(); j++) {
                row.push_back(seats[j]);
                if ((j + 1 - i) % 3 == 0 && j < i + 8) { // oddziałka co 3 miejsce w kolumnie
                    row.push_back(separator());
                }
            }
            document.push_back(hbox(row));
            if (i + 9 < seats.size()) {
                document.push_back(separator());
            }
        }
    }

    auto containerWithSelectedSeats = vbox({
                                                   hbox({
                                                                text(L" MENU MIEJSC W SAMOLOCIE") | bold}) | color(Color::Blue) | hcenter,
                                                   separator(),
                                                   vbox(document) | hcenter,
                                                   separator(),
                                                   text(" ") | bold | hcenter,
                                                   text("To wszystkie miejsca w samolocie.") | bold | hcenter,
                                           }) | style;

    auto userScreenWithSelectedSeats = Screen::Create(Dimension::Fit(containerWithSelectedSeats), Dimension::Fit(containerWithSelectedSeats));
    Render(userScreenWithSelectedSeats, containerWithSelectedSeats);
    std::cout << userScreenWithSelectedSeats.ToString() << '\0' << std::endl;
}
