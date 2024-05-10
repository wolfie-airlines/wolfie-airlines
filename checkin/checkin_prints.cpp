#include "checkin_prints.h"

#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../qr_code/qrcode_prints.h"
#include "../user/user_functions/user_tickets/user_tickets_prints.h"
#include "ftxui/dom/elements.hpp"

const std::string CHECKIN_SCREEN_TITLE = "ODPRAWA BILETOWA";
const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";

std::shared_ptr<ftxui::Element> CreateCheckinScreen(const std::string &message) {
    auto summary = ftxui::vbox({
        ftxui::hbox({ftxui::paragraphAlignCenter(CHECKIN_SCREEN_TITLE)}) | color(ftxui::Color::GrayDark),
        ftxui::separator(),
        ftxui::hbox({ftxui::paragraphAlignRight(message)}) | color(ftxui::Color::LightSteelBlue),
    });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter(AIRPORT_NAME), summary)});
    return std::make_shared<ftxui::Element>(document);
}

void PrintCheckinScreen(User &user) {
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

    // jeśli wszystkie bilety są już odprawione, też nie ma sensu wykonywać tej funkcji
    bool all_checked_in = true;
    for (const auto &flight : user_flights) {
        if (!flight["checkin"].get_bool().value) {
            all_checked_in = false;
            break;
        }
    }

    if (all_checked_in) {
        PrintErrorMessage("You do not have any tickets to check in.", "");
        return;
    }

    std::optional<std::string> option = CreateTicketsScreen(user, true);
    if (option == "quit") {
        PrintErrorMessage("Cancelled check-in.",
                          "Ticket check-in has been canceled. You can always come back to it another time.");
    } else if (option == "select") {
        auto checkin_screen = CreateCheckinScreen("Enter the NUMBER of the flight you would like to check in for:");
        PrintScreen(checkin_screen);

        int flight_number;
        std::cin >> flight_number;

        if (flight_number < 1 || flight_number > user_flights.length()) {
            PrintErrorMessage("There is no such flight.", "Try again.");
            return;
        }

        if (user_flights[flight_number - 1]["checkin"].get_bool().value) {
            PrintErrorMessage("This flight has already been through the check-in.", "Pick another flight.");
            return;
        }

        std::string flightId = (std::string)user_flights[flight_number - 1]["flightId"].get_string().value;
        std::vector<int> seats;
        for (const auto &seat : user_flights[flight_number - 1]["seats"].get_array().value) {
            seats.push_back(seat.get_int32().value);
        }

        auto qr_info_screen = CreateCheckinScreen("Scan the QR code below to check in. Yes, it's that easy!");
        PrintScreen(qr_info_screen);

        CreateQr(user.email_, user.username_, flightId, seats);
    }
}
