#include "tickets.h"
#include "../functions/info_print_functions.h"
#include "../flights/flights_functions/flight_prints/flight_print_functions.h"
#include "../plane/plane.h"
#include "tickets_prints/tickets_print_functions.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"

void processPurchase(
        FlightConnection& flightConnection,
        FlightConnection& foundConnection,
        User& user) {
    using namespace ftxui;
    std::string flight_identifier = foundConnection.getIdentifier();
    std::string ticketAmountInput;
    int ticketAmount = 0;
    while (true) {
        //TODO: Zmienić na ftxui
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
        // TODO: Zmienić na ftxui
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
        // TODO: Zmienić na ftxui
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

    if(user.discount != 1) {
        user.updateMoneySaved(foundConnection.getPrice() * ticketAmount, price);
    }

    flightConnection.updateSeatsTaken(flight_identifier, selectedSeats);
    user.addTicketToUser(selectedSeats, foundConnection);
}


void handleSingleTicket(FlightConnection& flightConnection, User& user) {
    std::string flightId;
    std::cout << "Podaj identyfikator lotu: ";
    std::cin >> flightId;

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
    if(seatsTaken.size() == 0) {
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
        handleSingleTicket(flightConnection, user);
    }
}

void handleTicketChoice(FlightConnection& connection, User& user) {
    int choice = CreateTicketMenu();
    handleBuyTicket(choice, connection, user);
}