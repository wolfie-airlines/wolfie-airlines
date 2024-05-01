#include "tickets.h"
#include "../functions/info_print_functions.h"
#include "../flights/flights_functions/flight_prints/flight_print_functions.h"
#include "../plane/plane.h"
#include "tickets_prints/tickets_print_functions.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include <random>

void processPurchase(
        FlightConnection& flightConnection,
        FlightConnection& foundConnection,
        User& user) {
    using namespace ftxui;
    std::string flight_identifier = foundConnection.getIdentifier();
    std::vector<int> seatsTaken = flightConnection.getSeatsTaken(flight_identifier);
    int ticketAmount;
    while (true) {
        std::string ticketAmountInput = displayMessageAndCaptureInput(
                "Zakup biletów",
                "Podaj liczbę biletów do kupienia (minimalnie 1 do maksymalnie 4):"
        );

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
    bool hasPrivilege = user.discountType == "ulga";

    for (int i = 0; i < ticketAmount; i++) {
        int seat;
        while (true) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 81);
            seat = dis(gen);
            if (std::find(seatsTaken.begin(), seatsTaken.end(), seat) == seatsTaken.end()) {
                if (hasPrivilege && (seat == 37 || seat == 45)) {
                    if (std::count_if(seatsTaken.begin(), seatsTaken.end(), [](int i){return i != 37 && i != 45;}) == 79) {
                        std::string response = displayWarningAndCaptureInput("Uwaga!", "Jedynymi dostępnymi miejscami są miejsca awaryjne (37 i 45). Czy chcesz kontynuować? (tak/nie)");
                        if (response == "tak" || response == "TAK" || response == "Tak") {
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
        selectedSeats.push_back(seat);
    }

    std::string confirmChoice;

    if(ticketAmount == 1) {
        confirmChoice = displayMessageAndCaptureInput(
                "Potwierdzenie zakupu biletów",
                "Czy na pewno chcesz kupić " + std::to_string(ticketAmount) + " bilet na lot " + foundConnection.getIdentifier() + " (tak/nie)"
        );
    } else {
        confirmChoice = displayMessageAndCaptureInput(
                "Potwierdzenie zakupu biletów",
                "Czy na pewno chcesz kupić " + std::to_string(ticketAmount) + " bilety na lot " + foundConnection.getIdentifier() + " (tak/nie)"
        );
    }

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

    if(user.discount != 1) {
        user.updateMoneySaved(foundConnection.getPrice() * ticketAmount, price);
    }

    flightConnection.updateSeatsTaken(flight_identifier, selectedSeats);
    user.addTicketToUser(selectedSeats, foundConnection);
    printTicketInvoice(user, foundConnection, selectedSeats);
}

void handleFlightById(FlightConnection& flightConnection, User& user) {
    std::string flightId = displayMessageAndCaptureInput(
            "Zakup biletów",
            "Podaj identyfikator lotu:"
    );

    FlightConnection foundConnection = flightConnection.findConnectionById(flightId);


    if (foundConnection.getIdentifier() != flightId) {
        errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        return;
    }

    CreateFoundFlightScreen(foundConnection, user);
    bool validFlightChoice = validChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
    if(!validFlightChoice) {
        errorFunction("Nie wybrano lotu.", "Spróbuj ponownie.");
        return;
    }

    std::vector<int> seatsTaken = flightConnection.getSeatsTaken(flightId);
    if(seatsTaken.size() == 81) {
        errorFunction("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
        return;
    }
    std::string premiumCard = user.premiumCard;
    if(premiumCard == "platynowa") {
        processSeatSelectionAndPurchase(seatsTaken, flightConnection, foundConnection, user);
    } else {
        processPurchase(flightConnection, foundConnection, user);
    }
}

void handleFlightByData(FlightConnection& flightConnection, User& user) {
    std::string departureCity = displayMessageAndCaptureInput(
            "Zakup biletów",
            "Podaj miasto wylotu:"
    );

    std::string arrivalCity = displayMessageAndCaptureInput(
            "Zakup biletów",
            "Podaj miasto przylotu:"
    );

    std::vector<FlightConnection> foundArrivalConnections = flightConnection.findConnectionsByDestination(arrivalCity);
    std::vector<FlightConnection> foundDepartureConnections = flightConnection.findConnectionsByDeparture(departureCity);

    if (foundArrivalConnections.empty() || foundDepartureConnections.empty()) {
        errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        return;
    }

    FlightConnection foundConnection = flightConnection.findConnection(departureCity, arrivalCity);

    if (foundConnection.getDepartureCity() != departureCity || foundConnection.getDestinationCity() != arrivalCity) {
        errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        return;
    }

    CreateFoundFlightScreen(foundConnection, user);
    bool validFlightChoice = validChoice("POTWIERDŹ WYBRANIE LOTU", "Czy o ten lot chodziło? (tak/nie)");
    if(!validFlightChoice) {
        errorFunction("Nie wybrano lotu.", "Spróbuj ponownie.");
        return;
    }

    std::vector<int> seatsTaken = flightConnection.getSeatsTaken(foundConnection.getIdentifier());
    if(seatsTaken.size() == 81) {
        errorFunction("Brak miejsc na pokładzie.", "Spróbuj wybrać inny lot.");
        return;
    }
    std::string premiumCard = user.premiumCard;
    if(premiumCard == "platynowa") {
        processSeatSelectionAndPurchase(seatsTaken, flightConnection, foundConnection, user);
    } else {
        processPurchase(flightConnection, foundConnection, user);
    }
}

void handleBuyTicket(int choice, FlightConnection& flightConnection, User& user) {
    if(choice == 0) {
        handleFlightById(flightConnection, user);
    } else if (choice == 1) {
        handleFlightByData(flightConnection, user);
    }
}

void handleTicketChoice(FlightConnection& connection, User& user) {
    int choice = CreateTicketMenu();
    handleBuyTicket(choice, connection, user);
}