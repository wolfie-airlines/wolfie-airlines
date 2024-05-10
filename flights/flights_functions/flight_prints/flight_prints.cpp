#include "flight_prints.h"

#include <iostream>

#include "../../../functions/info_prints/info_prints.h"
#include "../../../functions/main_prints/main_prints.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

int CreateFlightChoiceScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
        "View a list of all flights",
        "Find a connection (specifying the city of departure and arrival)",
        "Find a connection (by providing the Identifier <ID> of the flight)",
        "Find a connection (specifying price range)",
        "Find connection (specifying city of departure) - will return all connections from that city",
        "Find connection (specifying city of arrival) - will return all connections to that city",
        "\U0001F519 Return to main menu",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

std::string PageSizeString(int totalPages) {
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

    auto make_strike_box =
        [](const std::string &title, int dimx, int dimy, const std::string &oldContent, const std::string &newContent) {
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

    int current_page = 1;
    int total_pages = (connections.size() + PAGE_SIZE - 1) / PAGE_SIZE;
    std::string menu_page_string = total_pages == 1 ? " " : PageSizeString(total_pages);

    while (true) {
        int start_index = (current_page - 1) * PAGE_SIZE;
        int end_index = std::min<int>(start_index + PAGE_SIZE, connections.size());

        document.clear();
        std::string premium_card = user.premium_card_;
        double user_discount = user.discount_;

        double discount;
        if (premium_card == "blue" || premium_card == "gold") {
            discount = 0.95;
        } else if (premium_card == "platinum") {
            discount = 0.85;
        } else if (user_discount != 1) {
            discount = user_discount;
        }

        for (int i = start_index; i < end_index; i++) {
            document.push_back(
                ftxui::hbox({
                    make_box("FLIGHT ID", 25, 5, connections[i].GetIdentifier()),
                    make_box("SEATS", 25, 5, std::to_string(connections[i].GetAvailableSeats())),
                    make_box("DEPARTURE TIME", 50, 5, connections[i].GetDepartureTime()),
                    make_box("DEPARTURE", 50, 5, connections[i].GetDepartureCity()),
                    make_box("DESTINATION", 50, 5, connections[i].GetDestinationCity()),
                    make_box("ARRIVAL TIME", 50, 5, connections[i].GetArrivalTime()),
                    (premium_card != "none" || user_discount != 1)
                        ? make_strike_box("PRICE", 40, 5, std::to_string((int)connections[i].GetPrice()),
                                          std::to_string((int)(connections[i].GetPrice() * discount)) + " PLN")
                        : make_box("PRICE", 25, 5, std::to_string((int)connections[i].GetPrice()) + " PLN"),
                }));
        }

        auto container = ftxui::vbox({
                             ftxui::hbox({ftxui::text(L" CONNECTION MENU") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter,
                             ftxui::separator(),
                             ftxui::vbox(document),
                             ftxui::separator(),
                             total_pages != 1 ? ftxui::text(
                                                    "Page " + std::to_string(current_page) + "/" + std::to_string(total_pages)) |
                                                    ftxui::bold | ftxui::hcenter
                                              : ftxui::text(" ") | ftxui::bold | ftxui::hcenter,
                             total_pages != 1 ? ftxui::hbox({ftxui::text(
                                                                 "Switch between pages by typing the page number: " + menu_page_string) |
                                                             ftxui::bold}) |
                                                    color(ftxui::Color::YellowLight) | ftxui::hcenter
                                              : ftxui::text("These are all the flights we were able to find.") | ftxui::bold | ftxui::hcenter,
                             total_pages != 1 ? ftxui::hbox({ftxui::text("You can close the menu by typing: quit/cancel/exit") | ftxui::bold}) | color(ftxui::Color::DarkOrange) | ftxui::hcenter
                                              : ftxui::text("Thank you for using our services!") | color(ftxui::Color::DarkOliveGreen2) | ftxui::bold | ftxui::hcenter,
                         }) |
                         style;

        PrintFullWidthScreen(container);

        if (total_pages != 1) {
            std::string input;
            std::cin >> input;

            if (input == "quit" || input == "cancel" || input == "exit") {
                break;
            }

            try {
                int input_page = std::stoi(input);
                current_page = std::clamp(input_page, 1, total_pages);
            } catch (std::invalid_argument &e) {
                PrintErrorMessage("Invalid selection.", "There was a return to the main menu.");
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

    auto make_strike_box =
        [](const std::string &title, int dimx, int dimy, const std::string &oldContent, const std::string &newContent) {
            return window(ftxui::text(title) | ftxui::hcenter | ftxui::bold,
                          ftxui::hbox(
                              ftxui::strikethrough(ftxui::text(oldContent)) | ftxui::hcenter | ftxui::color(ftxui::Color::Red),
                              ftxui::text(" " + newContent) | ftxui::hcenter | ftxui::color(ftxui::Color::Green)) |
                              ftxui::center) |
                   size(ftxui::WIDTH, ftxui::EQUAL, dimx);
        };

    auto style = size(ftxui::WIDTH, ftxui::GREATER_THAN, 150) | ftxui::border;

    std::vector<ftxui::Element> boxes;

    std::string premium_card = user.premium_card_;
    double user_discount = user.discount_;
    double discount;
    if (premium_card == "blue") {
        discount = 0.95;
    } else if (premium_card == "gold") {
        discount = 0.95;
    } else if (premium_card == "platinum") {
        discount = 0.85;
    } else if (user_discount != 1) {
        discount = user_discount;
    }

    auto container = ftxui::vbox({
                         ftxui::hbox({ftxui::text(L" CONNECTION FOUND") | ftxui::bold}) | color(ftxui::Color::Blue) | ftxui::hcenter,
                         ftxui::separator(),
                         ftxui::vbox({
                             ftxui::hbox({
                                 make_box("FLIGHT ID",
                                          25,
                                          5,
                                          connection.GetIdentifier()),
                                 make_box("SEATS",
                                          25,
                                          5,
                                          std::to_string(connection.GetAvailableSeats())),
                                 make_box("DEPARTURE TIME",
                                          50,
                                          5,
                                          connection.GetDepartureTime()),
                                 make_box("DEPARTURE",
                                          50,
                                          5,
                                          connection.GetDepartureCity()),
                                 make_box("DESTINATION",
                                          50,
                                          5,
                                          connection.GetDestinationCity()),
                                 make_box("ARRIVAL TIME",
                                          50,
                                          5,
                                          connection.GetArrivalTime()),
                                 (premium_card != "none" || user_discount != 1)
                                     ? make_strike_box("PRICE",
                                                       45,
                                                       5,
                                                       std::to_string((int)connection.GetPrice()),
                                                       std::to_string((int)(connection.GetPrice() * discount)) + " PLN")
                                     : make_box("PRICE",
                                                25,
                                                5,
                                                std::to_string((int)connection.GetPrice()) + " PLN"),
                             }),
                         }),
                     }) |
                     style;

    PrintFullWidthScreen(container);
}
