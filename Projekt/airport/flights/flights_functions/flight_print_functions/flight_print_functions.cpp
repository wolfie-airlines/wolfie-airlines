#include <iostream>
#include "flight_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/component.hpp"

int CreateFlightChoiceScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
            "Wyświetl listę wszystkich lotów",
            "Znajdź połączenie (podając miasto wylotu i przylotu)",
            "Znajdź połączenie (podając Indentyfikator <ID> lotu)",
            "Znajdź połączenie (podając przedział cenowy, np. 100-200)",
            "Znajdź połączenie (podając miasto wylotu) - zwróci wszystkie połączenia z tego miasta",
            "Znajdź połączenie (podając miasto przylotu) - zwróci wszystkie połączenia do tego miasta",
            "↩️ Wróć do menu głównego",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}


std::shared_ptr<ftxui::Element> CreateFlightsScreen(const std::vector<FlightConnection>& connections) {
    auto make_box = [](const std::string &title, int dimx, int dimy, const std::string &content) {
        return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                      ftxui::text(content) | ftxui::hcenter | ftxui::dim) |
               size(ftxui::WIDTH, ftxui::EQUAL, dimx);
    };

    auto style = size(ftxui::WIDTH, ftxui::GREATER_THAN, 150) | ftxui::border |
                 size(ftxui::HEIGHT, ftxui::GREATER_THAN, 150);

    std::vector<ftxui::Element> boxes;
    std::cout << connections.size() << std::endl;

    ftxui::Elements document;

    for (int i=0; i < 8; i++) {
        document.push_back(ftxui::hbox({
                                               make_box("ID LOTU", 25, 5, connections[i].getIdentifier()),
                                               make_box("CZAS WYLOTU", 50, 5, connections[i].getDepartureTime()),
                                               make_box("MIEJSCE WYLOTU", 50, 5, connections[i].getDepartureCity()),
                                               make_box("MIEJSCE PRZYLOTU", 50, 5, connections[i].getDestinationCity()),
                                               make_box("GODZINA PRZYLOTU", 50, 5, connections[i].getArrivalTime()),
                                               make_box("CENA", 25, 5, std::to_string((int) connections[i].getPrice()) + " PLN"),
                                       }));
    }

    auto container = ftxui::vbox({
                                         ftxui::hbox({
                                                             ftxui::text(L" MENU POŁĄCZEŃ") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter ,
                                         ftxui::separator(),
                                         ftxui::vbox(document),
                                         ftxui::separator(),
                                         ftxui::hbox({ftxui::text(L"Strona 1/4") | ftxui::bold}) | color(ftxui::Color::YellowLight) | ftxui::hcenter ,
                                         ftxui::hbox({ftxui::text(L"Przełączaj się między stronami wpisując 1-4") | ftxui::bold}) | color(ftxui::Color::YellowLight) | ftxui::hcenter ,
                                 }) | style;
    return std::make_shared<ftxui::Element>(container);
}

