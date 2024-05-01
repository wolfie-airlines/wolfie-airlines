#include "flight_print_functions.h"

#include <iostream>

#include "../../../functions/info_print_functions.h"
#include "../../../functions/main_prints/main_prints.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

const int PAGE_SIZE = 9;

int CreateFlightChoiceScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
        "Wyświetl listę wszystkich lotów",
        "Znajdź połączenie (podając miasto wylotu i przylotu)",
        "Znajdź połączenie (podając Indentyfikator <ID> lotu)",
        "Znajdź połączenie (podając przedział cenowy)",
        "Znajdź połączenie (podając miasto wylotu) - zwróci wszystkie połączenia z tego miasta",
        "Znajdź połączenie (podając miasto przylotu) - zwróci wszystkie połączenia do tego miasta",
        "\U0001F519 Wróć do menu głównego",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

std::string PAGE_SIZEString(int totalPages) {
    // budowanie napisu dla menu w formie slashy
    std::string result;
    for (int i = 1; i <= totalPages; i++) {
        result += std::to_string(i);
        if (i != totalPages) {
            result += "/";
        }
    }
    return result;
}

void CreateAllFlightsScreen(const std::vector<FlightConnection> &connections, User &user) {
    auto make_box = [](const std::string &title, int dimx, int dimy, const std::string &content) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::text(content) | ftxui::hcenter | ftxui::dim) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto make_strike_box = [](const std::string &title, int dimx, int dimy, const std::string &oldContent, const std::string &newContent) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::hbox(
                          ftxui::strikethrough(ftxui::text(oldContent)) | ftxui::hcenter | ftxui::color(ftxui::Color::Red),
                          ftxui::text(" " + newContent) | ftxui::hcenter | ftxui::color(ftxui::Color::Green)) |
                          ftxui::center) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto style = size(ftxui::WIDTH, ftxui::GREATER_THAN, 150) | ftxui::border;

    std::vector<ftxui::Element> boxes;

    ftxui::Elements document;

    int currentPage = 1;
    int totalPages = (connections.size() + PAGE_SIZE - 1) / PAGE_SIZE;
    std::string menuPageString = totalPages == 1 ? " " : PAGE_SIZEString(totalPages);

    while (true) {
        int startIndex = (currentPage - 1) * PAGE_SIZE;
        int endIndex = std::min<int>(startIndex + PAGE_SIZE, connections.size());

        document.clear();
        std::string premiumCard = user.premiumCard;
        double userDiscount = user.discount;

        double discount;
        if (premiumCard == "niebieska" || premiumCard == "złota") {
            discount = 0.95;
        } else if (premiumCard == "platynowa") {
            discount = 0.85;
        } else if (userDiscount != 1) {
            discount = userDiscount;
        }

        for (int i = startIndex; i < endIndex; i++) {
            document.push_back(ftxui::hbox({
                make_box("ID LOTU", 25, 5, connections[i].getIdentifier()),
                make_box("MIEJSCA", 25, 5, std::to_string(connections[i].getAvailableSeats())),
                make_box("CZAS WYLOTU", 50, 5, connections[i].getDepartureTime()),
                make_box("MIEJSCE WYLOTU", 50, 5, connections[i].getDepartureCity()),
                make_box("MIEJSCE PRZYLOTU", 50, 5, connections[i].getDestinationCity()),
                make_box("CZAS PRZYLOTU", 50, 5, connections[i].getArrivalTime()),
                (premiumCard != "brak" || userDiscount != 1) ? make_strike_box("CENA", 40, 5, std::to_string((int)connections[i].getPrice()), std::to_string((int)(connections[i].getPrice() * discount)) + " PLN")
                                                             : make_box("CENA", 25, 5, std::to_string((int)connections[i].getPrice()) + " PLN"),
            }));
        }

        auto container = ftxui::vbox({
                             ftxui::hbox({ftxui::text(L" MENU POŁĄCZEŃ") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter,
                             ftxui::separator(),
                             ftxui::vbox(document),
                             ftxui::separator(),
                             totalPages != 1 ? ftxui::text("Strona " + std::to_string(currentPage) + "/" + std::to_string(totalPages)) | ftxui::bold | ftxui::hcenter : ftxui::text(" ") | ftxui::bold | ftxui::hcenter,
                             totalPages != 1 ? ftxui::hbox({ftxui::text("Przełączaj się między stronami wpisując numer strony: " + menuPageString) | ftxui::bold}) | color(ftxui::Color::YellowLight) | ftxui::hcenter : ftxui::text("To wszystkie loty jakie byliśmy w stanie znaleźć.") | ftxui::bold | ftxui::hcenter,
                             totalPages != 1 ? ftxui::hbox({ftxui::text("Możesz zamknąć menu wpisując: quit/cancel/exit") | ftxui::bold}) | color(ftxui::Color::DarkOrange) | ftxui::hcenter : ftxui::text("Dziękujemy za skorzystanie z naszych usług!") | color(ftxui::Color::DarkOliveGreen2) | ftxui::bold | ftxui::hcenter,
                         }) |
                         style;

        printFullWidthScreen(container);

        if (totalPages != 1) {
            std::string input;
            std::cin >> input;

            if (input == "quit" || input == "cancel" || input == "exit") {
                break;
            }

            try {
                int inputPage = std::stoi(input);
                currentPage = std::clamp(inputPage, 1, totalPages);
            } catch (std::invalid_argument &e) {
                errorFunction("Nieprawidłowy wybór.", "Nastąpił powrót do głównego menu.");
                return;
            }

        } else {
            break;
        }
    }
}

void CreateFoundFlightScreen(FlightConnection &connection, User &user) {
    auto make_box = [](const std::string &title, int dimx, int dimy, const std::string &content) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::text(content) | ftxui::hcenter | ftxui::dim) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto make_strike_box = [](const std::string &title, int dimx, int dimy, const std::string &oldContent, const std::string &newContent) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::hbox(
                          ftxui::strikethrough(ftxui::text(oldContent)) | ftxui::hcenter | ftxui::color(ftxui::Color::Red),
                          ftxui::text(" " + newContent) | ftxui::hcenter | ftxui::color(ftxui::Color::Green)) |
                          ftxui::center) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto style = size(ftxui::WIDTH, ftxui::GREATER_THAN, 150) | ftxui::border;

    std::vector<ftxui::Element> boxes;

    std::string premiumCard = user.premiumCard;
    double userDiscount = user.discount;
    double discount;
    if (premiumCard == "niebieska") {
        discount = 0.95;
    } else if (premiumCard == "złota") {
        discount = 0.95;
    } else if (premiumCard == "platynowa") {
        discount = 0.85;
    } else if (userDiscount != 1) {
        discount = userDiscount;
    }

    auto container = ftxui::vbox({
                         ftxui::hbox({ftxui::text(L" ZNALEZIONE POŁĄCZENIE") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter,
                         ftxui::separator(),
                         ftxui::vbox({
                             ftxui::hbox({
                                 make_box("ID LOTU", 25, 5, connection.getIdentifier()),
                                 make_box("MIEJSCA", 25, 5, std::to_string(connection.getAvailableSeats())),
                                 make_box("CZAS WYLOTU", 50, 5, connection.getDepartureTime()),
                                 make_box("MIEJSCE WYLOTU", 50, 5, connection.getDepartureCity()),
                                 make_box("MIEJSCE PRZYLOTU", 50, 5, connection.getDestinationCity()),
                                 make_box("CZAS PRZYLOTU", 50, 5, connection.getArrivalTime()),
                                 (premiumCard != "brak" || userDiscount != 1) ? make_strike_box("CENA", 45, 5, std::to_string((int)connection.getPrice()), std::to_string((int)(connection.getPrice() * discount)) + " PLN") : make_box("CENA", 25, 5, std::to_string((int)connection.getPrice()) + " PLN"),
                             }),
                         }),
                     }) |
                     style;

    printFullWidthScreen(container);
}
