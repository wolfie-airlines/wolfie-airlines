#include "luggage_prints.h"

#include "../../functions/info_prints/info_prints.h"
#include "../../functions/main_prints/main_prints.h"
#include "../../user/user_functions/user_payments/user_payment_functions.h"
#include "../../user/user_functions/user_tickets/user_tickets_prints.h"
#include "../item/item_handler.h"
#include "../luggage_handler.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"

std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components) {
    std::vector<ftxui::Component> vertical_containers;
    for (size_t i = 0; i < checkbox_components.size(); i += 8) {
        std::vector<ftxui::Component> group;
        for (size_t j = i; j < i + 8 && j < checkbox_components.size(); ++j) {
            group.push_back(checkbox_components[j]);
        }
        vertical_containers.push_back(ftxui::Container::Vertical(group));
    }
    return vertical_containers;
}

void PrintSpecificItem(Item &item) {
    std::string
        description = item.GetDescription().empty() ? "No detailed description of the object" : item.GetDescription();

    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << item.GetWeight();
    std::string weight = stream.str();

    std::vector<ftxui::Element> elements;
    std::vector<std::string> hints = item.GetHints();

    if (!hints.empty()) {
        std::vector<ftxui::Element> hint_elements;
        for (const auto &hint : hints) {
            std::string hint_with_bullet = "• " + hint;
            hint_elements.push_back(ftxui::paragraph(hint_with_bullet) | ftxui::color(ftxui::Color::White));
        }

        auto hint_box = ftxui::vbox(std::move(hint_elements));

        elements.push_back(ftxui::hbox({ftxui::text("Important informations: ") | ftxui::bold | ftxui::color(ftxui::Color::DarkSeaGreen2),
                                        hint_box}));
    }

    const std::string &profession = item.GetProfession();
    ftxui::Element profession_element = ftxui::hbox({});
    if (!profession.empty()) {
        profession_element = ftxui::hbox({ftxui::text("Available in any quantity for the profession: ") | ftxui::bold | ftxui::color(ftxui::Color::Gold1),
                                          ftxui::text(profession) | ftxui::color(ftxui::Color::White)});
    }

    auto create_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter(ITEM_CARD) | ftxui::bold}) | color(ftxui::Color::Orange3),
            ftxui::separator(),
            ftxui::hbox({ftxui::paragraphAlignCenter(item.GetItemName()) | ftxui::bold}) | color(ftxui::Color::Orange1),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Item: ") | ftxui::bold | color(ftxui::Color::SkyBlue1),
                         ftxui::text(item.GetItemName()) | color(ftxui::Color::White)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Item description: ") | ftxui::bold | color(ftxui::Color::DarkSeaGreen2),
                         ftxui::paragraph(description) | color(ftxui::Color::White)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Prohibited in air transportation: ") | ftxui::bold | color(ftxui::Color::RedLight),
                         ftxui::text(item.IsForbidden() ? "YES" : "NO") | color(
                                                                              item.IsForbidden() ? ftxui::Color::RedLight
                                                                                                 : ftxui::Color::GreenLight)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Carriage in registered baggage: ") | ftxui::bold | color(ftxui::Color::Aquamarine1),
                         ftxui::text(item.IsRegisteredLuggage() ? "✅" : "❌")}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Carriage in hand baggage: ") | ftxui::bold | color(ftxui::Color::MediumOrchid3),
                         ftxui::text(item.IsHandLuggage() ? "✅" : "❌")}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Pilot approval required: ") | ftxui::bold | color(ftxui::Color::LightSkyBlue1),
                         ftxui::text(item.IsPilotAllowance() ? "✅" : "❌")}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Maximum quantity (pieces): ") | ftxui::bold | color(ftxui::Color::LightCoral),
                         ftxui::text(std::to_string((int)item.GetMaxCount())) | color(ftxui::Color::Salmon1)}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text("Weight (of one item): ") | ftxui::bold | color(ftxui::Color::SandyBrown),
                         ftxui::text(weight + " kg") | color(ftxui::Color::LightPink1)}),
            ftxui::separator(),
            elements.empty() ? ftxui::hbox({}) : ftxui::hbox(elements),
            ftxui::separator(),
            profession_element,
        });

        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen =
        ftxui::Screen::Create(ftxui::Dimension::Fit(*create_screen()), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;
}

void PrintAllItems(User &user) {
    int page = 0;
    auto collection = user.GetSpecificCollection("luggage_list");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto &&doc : cursor) {
        documents.push_back(doc);
    }

    std::vector<Item> items = GetItems(user);
    int total_pages = (items.size() + 7) / 8;

    while (true) {
        std::vector<std::vector<std::string>> rows;
        for (int i = page * 8; i < (page + 1) * 8 && i < items.size(); i++) {
            const auto &item = items[i];
            std::string is_forbidden_string = item.IsForbidden() ? "YES" : "NO";
            std::string is_registered_luggage_string = item.IsRegisteredLuggage() ? "✅" : "❌";
            std::string is_hand_luggage_string = item.IsHandLuggage() ? "✅" : "❌";
            std::string is_pilot_allowance_string = item.IsPilotAllowance() ? "✅" : "❌";
            rows.push_back({std::to_string(i + 1),
                            item.GetItemName(),
                            is_forbidden_string,
                            is_registered_luggage_string,
                            is_hand_luggage_string,
                            is_pilot_allowance_string});
        }

        std::vector<std::string> header = {"NUMBER", "ITEM", "PROHIBITED", "REGISTERED BAGGAGE", "HAND BAGGAGE",
                                           "PILOT'S APPROVAL"};
        rows.insert(rows.begin(), header);

        auto table = ftxui::Table(rows);
        table.SelectAll().Border(ftxui::LIGHT);

        // Pierwszy rząd na grubo, żeby było widać, że to nagłówek
        table.SelectRow(0).Decorate(ftxui::bold);
        table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
        table.SelectRow(0).Border(ftxui::LIGHT);

        // Margin kolumn
        table.SelectColumns(0, 5).DecorateCells(ftxui::center);

        // Kolory numerów
        table.SelectColumn(0).DecorateCells(ftxui::color(ftxui::Color::DarkOliveGreen3));

        // Kolory przedmiotów
        table.SelectColumn(1).DecorateCells(ftxui::color(ftxui::Color::SkyBlue1));

        // Kolory zabronionych przedmiotów
        for (int i = 0; i < rows.size(); i++) {
            if (rows[i][2] == "YES") {
                table.SelectCell(2, i).DecorateCells(ftxui::color(ftxui::Color::RedLight));
            } else {
                table.SelectCell(2, i).DecorateCells(ftxui::color(ftxui::Color::White));
            }
        }

        // Kolory bagażu rejestrowanego
        table.SelectColumn(3).DecorateCells(ftxui::color(ftxui::Color::Aquamarine1));

        // Kolory bagażu podręcznego
        table.SelectColumn(4).DecorateCells(ftxui::color(ftxui::Color::MediumOrchid3));

        // Kolory zgody pilota
        table.SelectColumn(5).DecorateCells(ftxui::color(ftxui::Color::LightSkyBlue1));

        // Oddziałka między wierszami
        for (int i = 2; i < 9; i++) {
            table.SelectRow(i).Border(ftxui::LIGHT);
        }

        // Oddziałka między kolumnami
        for (int i = 1; i < 6; i++) {
            table.SelectColumn(i).Border(ftxui::LIGHT);
        }

        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::paragraphAlignCenter("LIST OF ALL ITEMS")}) |
                color(ftxui::Color::GrayDark),
            table.Render(),
            ftxui::hbox({
                ftxui::paragraphAlignRight("Page " + std::to_string(page + 1) + "/" + std::to_string(total_pages)) | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
            }),
            ftxui::vbox({
                ftxui::separator(),
                ftxui::hbox({
                    ftxui::text("🧭 NAVIGATION") | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
                }),
                ftxui::separator(),
                ftxui::hbox({
                    ftxui::text("next. Next page") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                }),
                ftxui::hbox({
                    ftxui::text("prev. Previous page") | ftxui::color(ftxui::Color::DarkOliveGreen2) | ftxui::bold,
                }),
                ftxui::hbox({ftxui::text("quit. \U0001f51a  Exit the list") | ftxui::color(ftxui::Color::RedLight) | ftxui::bold}),
                ftxui::separator(),
                ftxui::hbox({
                    ftxui::text(
                        "Select the item number to see the display of its details") |
                        ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
                }),
            }),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});

        PrintNodeScreen(document);

        std::string response;
        std::cin >> response;
        if (response == "next") {
            if (page == total_pages - 1) {
                continue;
            }
            page++;
        } else if (response == "prev") {
            if (page == 0) {
                continue;
            }
            page--;
        } else if (response == "quit") {
            return;
        } else {
            try {
                int item_number = std::stoi(response);
                if (item_number >= 1 && item_number <= 34) {
                    int index = item_number - 1;
                    if (index < items.size()) {
                        PrintSpecificItem(items[index]);
                    }
                } else {
                    PrintErrorMessage("There is no such item!", "Dial the correct number");
                    continue;
                }
            } catch (std::invalid_argument &e) {
                continue;
            }
        }
    }
}

void PrintWelcomeInCheckIn(User &user) {
    mongocxx::cursor cursor = user.FindUserInDatabase();
    if (cursor.begin() == cursor.end()) {
        PrintErrorMessage("The user was not found in the database.", "Log in again.");
        return;
    }

    bsoncxx::document::view user_view = *cursor.begin();
    bsoncxx::document::element user_flights_element = user_view["userFlights"];
    bsoncxx::array::view user_flights = user_flights_element.get_array().value;

    if (user_flights.begin() == user_flights.end()) {
        PrintErrorMessage("You don't have any tickets.", "Purchase them now using option 2!");
        return;
    }

    bool all_checked_in = true;
    for (const auto &flight : user_flights) {
        if (!flight["luggageCheckin"].get_bool().value) {
            all_checked_in = false;
            break;
        }
    }

    if (all_checked_in) {
        PrintErrorMessage("Do not have any tickets to check in.", "");
        return;
    }

    std::optional<std::string> option = CreateTicketsScreen(user, true);
    if (option == "quit") {
        PrintErrorMessage("Cancelled checkin",
                          "Baggage check-in has been canceled. You can always come back to it another time.");
    } else if (option == "select") {
        auto checkin_screen = [&] {
            auto summary = ftxui::vbox({
                ftxui::hbox({ftxui::paragraphAlignCenter("BAGGAGE CHECK-IN")}) |
                    color(ftxui::Color::GrayDark),
                ftxui::separator(),
                ftxui::hbox({ftxui::paragraphAlignRight(
                    "Enter the FLIGHT NUMBER for which you would like to check in your luggage:")}) |
                    color(ftxui::Color::LightSteelBlue),
            });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            return std::make_shared<ftxui::Element>(document);
        };

        auto final_checkin_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(*checkin_screen()),
                                                          ftxui::Dimension::Fit(*checkin_screen()));
        ftxui::Render(final_checkin_screen, *checkin_screen());
        std::cout << final_checkin_screen.ToString() << '\0' << std::endl;

        int flight_number;
        std::cin >> flight_number;

        if (flight_number < 1 || flight_number > user_flights.length()) {
            PrintErrorMessage("There is no such flight.", "Try again.");
            return;
        }

        if (user_flights[flight_number - 1]["luggageCheckin"].get_bool().value) {
            PrintErrorMessage("This flight has already been through baggage checkin", "Pick another flight.");
            return;
        }

        auto create_screen = [&] {
            auto summary = ftxui::vbox({
                ftxui::hbox({ftxui::text(user.username_) |
                                 color(ftxui::Color::Gold1),
                             ftxui::text(", welcome to baggage check-in!")}) |
                    ftxui::bold | ftxui::center,
                ftxui::separator(),
                ftxui::vbox({ftxui::paragraphAlignCenter(
                                 "Before you start, you have the option to view a list of all permitted and prohibited items to take in your luggage.") |
                                 ftxui::bold | color(ftxui::Color::YellowLight),
                             ftxui::paragraphAlignCenter("Chcesz to zrobić? ") |
                                 ftxui::bold | color(ftxui::Color::Khaki3)}),
                ftxui::separator(),
                ftxui::vbox({
                    ftxui::hbox({
                        ftxui::text(
                            "yes. Displays a list of all items") |
                            ftxui::color(
                                ftxui::Color::CadetBlue) |
                            ftxui::bold,
                    }),
                    ftxui::hbox({
                        ftxui::text(
                            "no. Takes you to the next check-in screen") |
                            ftxui::color(
                                ftxui::Color::DarkOliveGreen2) |
                            ftxui::bold,
                    }),
                    ftxui::hbox({ftxui::text(
                                     "quit. \U0001f51a Ends the checkin") |
                                 ftxui::color(
                                     ftxui::Color::RedLight) |
                                 ftxui::bold}),
                }),
            });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
        ftxui::Render(user_screen, *create_screen());
        std::cout << user_screen.ToString() << '\0' << std::endl;

        std::string response;
        std::cin >> response;

        if (response == "yes" || response == "Yes" || response == "YES") {
            PrintAllItems(user);
        } else if (response == "no" || response == "No" || response == "NO") {
            CheckIn(user, flight_number);
        } else {
            return;
        }
    }
}
