#include "plane_prints.h"
#include <iostream>
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "../../functions/info_print_functions.h"
#include "../../user/user_functions/user_settings/user_payment_functions.h"


void processSeatSelectionAndPurchase(
        std::vector<int> seatsTaken,
        FlightConnection& flightConnection,
        FlightConnection& foundConnection,
        User& user) {
    using namespace ftxui;
    std::string planeId = "WOLFIE PLANE #";
    std::string flight_identifier = foundConnection.getIdentifier();
    for (char c : flight_identifier) {
        if (c != '-') {
            planeId += std::to_string(static_cast<int>(c));
        }
    }

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
                                               text(planeId) | bold}) | color(Color::Blue) | hcenter,
                                  separator(),
                                  vbox(document) | hcenter,
                                  separator(),
                                  text("LEGENDA") | ftxui::color(ftxui::Color::BlueLight) | bold | hcenter,
                                  ftxui::vbox({
                                                      ftxui::hbox({
                                                                          ftxui::text("\U0001f198 "),
                                                                          ftxui::text("- miejsce ewakuacyjne (wymagana znajomość angielskiego i brak zastrzeżeń lekarskich)") | ftxui::color(ftxui::Color::Orange1)
                                                                  }),
                                                      ftxui::hbox({
                                                                          ftxui::text("\u274C "),
                                                                          ftxui::text("- zajęte miejsce") | ftxui::color(ftxui::Color::Red1) | ftxui::bold
                                                                  }),
                                                      ftxui::hbox({
                                                                          ftxui::text("R ") | ftxui::color(ftxui::Color::Grey84) | ftxui::bold,
                                                                          ftxui::text("- rząd (numer rzędu),") | ftxui::color(ftxui::Color::Grey84),
                                                                          ftxui::text(" M ") | ftxui::color(ftxui::Color::Grey84) | ftxui::bold,
                                                                          ftxui::text("- miejsce (numer miejsca)") | ftxui::color(ftxui::Color::Grey84)
                                                                  }),
                                                }) | ftxui::hcenter,
                          }) | style;

    auto userScreen = Screen::Create(Dimension::Fit(container), Dimension::Fit(container));
    Render(userScreen, container);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string ticketAmountInput;
    int ticketAmount = 0;
    while (true) {
        std::cout << "Podaj liczbę biletów do kupienia (od 1 do 4) lub 'back' aby przerwać: ";
        std::cin >> ticketAmountInput;

        if (ticketAmountInput == "back") {
            errorFunction("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
            return;
        }

        try {
            ticketAmount = std::stoi(ticketAmountInput);
        } catch (std::invalid_argument& e) {
            errorFunction("Niepoprawna liczba biletów.", "Podaj liczbę biletów od 1 do 4.");
            return;
        }

        if (ticketAmount >= 1 && ticketAmount <= 4) {
            break;
        }
    }

    std::vector<int> selectedSeats;

    for (int i = 0; i < ticketAmount; ++i) {
        std::string rowInput;
        std::cout << "Podaj rząd dla biletu " << i + 1 << ": ";
        std::cin >> rowInput;
        int rowInputNumber;
        try {
            rowInputNumber = std::stoi(rowInput);
            if (rowInputNumber < 1 || rowInputNumber > 9) {
                errorFunction("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
                return;
            }
        } catch (std::invalid_argument& e) {
            errorFunction("Niepoprawny numer rzędu.", "Podaj numer rzędu od 1 do 9.");
            return;
        }
        std::string seatInput;
        std::cout << "Podaj miejsce dla biletu " << i + 1 << ": ";
        std::cin >> seatInput;
        int seat;
        try {
            seat = std::stoi(seatInput);
            if (seat < 1 || seat > 9) {
                errorFunction("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
                return;
            }
        } catch (std::invalid_argument& e) {
            errorFunction("Niepoprawny numer miejsca.", "Podaj numer miejsca od 1 do 9.");
            return;
        }

        int selectedSeatNumber = (rowInputNumber - 1) * 9 + seat;

        selectedSeats.push_back(selectedSeatNumber);
    }

    // aktualizacja zaznaczonych miejsc w samolocie
    for (int selectedSeat : selectedSeats) {
        seats[selectedSeat - 1] = make_seat_box(selectedSeat, true);
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
                                                                text(planeId) | bold}) | color(Color::Blue) | hcenter,
                                                   separator(),
                                                   vbox(document) | hcenter,
                                                   separator(),
                                                   text("Czy potwierdzasz wybrane miejsca? (tak)") | bold | hcenter,
                                                   text("Każdy inny wybór spowoduje anulowanie kupowania biletów.") | bold | hcenter,
                                           }) | style;

    auto userScreenWithSelectedSeats = Screen::Create(Dimension::Fit(containerWithSelectedSeats), Dimension::Fit(containerWithSelectedSeats));
    Render(userScreenWithSelectedSeats, containerWithSelectedSeats);
    std::cout << userScreenWithSelectedSeats.ToString() << '\0' << std::endl;

    std::string confirmChoice;
    std::cin >> confirmChoice;

    if (confirmChoice != "tak" && confirmChoice != "TAK" && confirmChoice != "Tak") {
        errorFunction("Anulowano zakup biletów.", "Możesz spróbować ponownie.");
        return;
    }

    std::string titleMessage = "Potwierdzenie zakupu biletów";
    int price = foundConnection.getPrice() * user.discount * ticketAmount;
    bool paymentSuccess = paymentAuth(user, user.paymentMethod, titleMessage, price);

    if (!paymentSuccess) {
        errorFunction("Nie udało się przetworzyć płatności.", "Zakup biletów został anulowany.");
        return;
    }

    flightConnection.updateSeatsTaken(flight_identifier, selectedSeats);

}
