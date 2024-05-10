#include "tickets.h"

#include <random>

#include "../flights/flights_functions/flight_prints/flight_prints.h"
#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "../plane/plane.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "tickets_prints/tickets_prints.h"

void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user) {
    using namespace ftxui;
    std::string flight_identifier = found_connection.GetIdentifier();
    std::vector<int> seats_taken = flight_connection.GetSeatsTaken(flight_identifier);
    int ticket_amount;
    while (true) {
        std::string amount_input = DisplayMessageAndCaptureStringInput(
            "Ticket purchase",
            "Enter the number of tickets to be purchased (minimum 1 to maximum " + std::to_string(MAX_TICKETS) + "):");

        if (amount_input == "back") {
            PrintErrorMessage("Ticket purchase cancelled.", "You can try again.");
            return;
        }

        try {
            ticket_amount = std::stoi(amount_input);
        } catch (std::invalid_argument &e) {
            PrintErrorMessage("ncorrect number of tickets.", "Enter the number of tickets from 1 to " + std::to_string(MAX_TICKETS));
            return;
        }

        if (ticket_amount >= 1 && ticket_amount <= MAX_TICKETS) {
            break;
        }
    }

    std::vector<int> selected_seats;
    bool has_privilege = user.discount_type_ == "ulti";

    for (int i = 0; i < ticket_amount; i++) {
        int seat;
        while (true) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 81);
            seat = dis(gen);
            if (std::find(seats_taken.begin(), seats_taken.end(), seat) == seats_taken.end()) {
                if (has_privilege && (seat == EMERGENCY_SEAT_ONE || seat == EMERGENCY_SEAT_TWO)) {
                    if (std::count_if(seats_taken.begin(),
                                      seats_taken.end(),
                                      [](int i) { return i != EMERGENCY_SEAT_ONE && i != EMERGENCY_SEAT_TWO; }) == 79) {
                        std::string response = DisplayWarningAndCaptureInput("Attention!",
                                                                             "The only places available are emergency sites: " + std::to_string(EMERGENCY_SEAT_ONE) + "i " + std::to_string(EMERGENCY_SEAT_TWO) + ". Do you want to continue? (yes/no)");
                        if (response == "yes" || response == "YES" || response == "Yes") {
                            break;
                        }
                    } else {
                        continue;
                    }
                } else {
                    break;
                }
            }
        }
        selected_seats.push_back(seat);
    }

    std::string choice;

    if (ticket_amount == 1) {
        choice = DisplayMessageAndCaptureStringInput(
            "Confirmation of ticket purchase",
            "Are you sure you want to buy " + std::to_string(ticket_amount) + " flight ticket for " +
                found_connection.GetIdentifier() + " (yes/no)");
    } else {
        choice = DisplayMessageAndCaptureStringInput(
            "Confirmation of ticket purchase",
            "Are you sure you want to buy " + std::to_string(ticket_amount) + " flight tickets for " +
                found_connection.GetIdentifier() + " (yes/no)");
    }

    if (choice != "yes" && choice != "YES" && choice != "Yes") {
        PrintErrorMessage("Cancelled Ticket purchase.", "You can try again.");
        return;
    }

    std::string title_message = "Confirmation of ticket purchase";
    int price = found_connection.GetPrice() * user.discount_ * ticket_amount;
    bool authenticate_payment = AuthenticatePayment(user, user.payment_method_, title_message, price);

    if (!authenticate_payment) {
        PrintErrorMessage("The payment could not be processed.", "Ticket purchase has been canceled.");
        return;
    }

    if (user.discount_ != 1) {
        user.UpdateMoneySaved(found_connection.GetPrice() * ticket_amount, price);
    }

    flight_connection.UpdateSeatsTaken(flight_identifier, selected_seats);
    user.AddTicketToUser(selected_seats, found_connection);
    PrintTicketInvoice(user, found_connection, selected_seats);
}

void HandleFlightById(FlightConnection &flight_connection, User &user) {
    std::string flight_id = DisplayMessageAndCaptureStringInput(
        "Ticket purchase",
        "Enter flight ID");

    FlightConnection found_connection = flight_connection.FindConnectionById(flight_id);

    if (found_connection.GetIdentifier() != flight_id) {
        PrintErrorMessage("No such flight was found.", "Try again.");
        return;
    }

    CreateFoundFlightScreen(found_connection, user);
    bool choice = ValidChoice("CONFIRM FLIGHT SELECTION", "Was that the flight you were looking for? (yes/no)");
    if (!choice) {
        PrintErrorMessage("The flight was not selected.", "Try again.");
        return;
    }

    std::vector<int> seats_taken = flight_connection.GetSeatsTaken(flight_id);
    if (seats_taken.size() == 81) {
        PrintErrorMessage("No seats on board.", "Try to choose another flight.");
        return;
    }
    std::string premium_card = user.premium_card_;
    if (premium_card == "platinum") {
        ProcessSeatSelectionAndPurchase(seats_taken, flight_connection, found_connection, user);
    } else {
        ProcessPurchase(flight_connection, found_connection, user);
    }
}

void HandleFlightByData(FlightConnection &flight_connection, User &user) {
    std::string departure_city = DisplayMessageAndCaptureStringInput(
        "Ticket purchase",
        "Enter departure city");

    std::string arrival_city = DisplayMessageAndCaptureStringInput(
        "Ticket purchase",
        "Enter destination city:");

    std::vector<FlightConnection> found_arrival_connections = flight_connection.FindConnectionsByDestination(arrival_city);
    std::vector<FlightConnection> found_departure_connections = flight_connection.FindConnectionsByDeparture(departure_city);

    if (found_arrival_connections.empty() || found_departure_connections.empty()) {
        PrintErrorMessage("No such flight was found.", "Try again.");
        return;
    }

    FlightConnection found_connection = flight_connection.FindConnection(departure_city, arrival_city);

    if (found_connection.GetDepartureCity() != departure_city || found_connection.GetDestinationCity() != arrival_city) {
        PrintErrorMessage("No such flight was found.", "Try again.");
        return;
    }

    CreateFoundFlightScreen(found_connection, user);
    bool choice = ValidChoice("CONFIRM FLIGHT SELECTION", "Was that the flight you were looking for? (yes/no)");
    if (!choice) {
        PrintErrorMessage("The flight was not selected.", "Try again.");
        return;
    }

    std::vector<int> seats_taken = flight_connection.GetSeatsTaken(found_connection.GetIdentifier());
    if (seats_taken.size() == 81) {
        PrintErrorMessage("No seats on board.", "Try to choose another flight.");
        return;
    }
    std::string premium_card = user.premium_card_;
    if (premium_card == "platinum") {
        ProcessSeatSelectionAndPurchase(seats_taken, flight_connection, found_connection, user);
    } else {
        ProcessPurchase(flight_connection, found_connection, user);
    }
}

void HandleBuyTicket(int choice, FlightConnection &flight_connection, User &user) {
    if (choice == 0) {
        HandleFlightById(flight_connection, user);
    } else if (choice == 1) {
        HandleFlightByData(flight_connection, user);
    }
}

void HandleTicketChoice(FlightConnection &flight_connection, User &user) {
    int choice = CreateTicketMenu();
    HandleBuyTicket(choice, flight_connection, user);
}