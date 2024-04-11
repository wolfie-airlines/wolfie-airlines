#include "ticket_functions.h"
#include "tickets_prints/tickets_print_functions.h"
#include "../../functions/info_print_functions.h"
#include "../../flights/flights_functions/flight_prints/flight_print_functions.h"

void handleSingleTicket(FlightConnection& flightConnection, User& user) {
    std::string flightId;
    std::cout << "Podaj identyfikator lotu: ";
    std::cin >> flightId;

    FlightConnection connection = flightConnection.findConnectionById(flightId);

    if (connection.getIdentifier() != flightId) {
        errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        return;
    }

    CreateFoundFlightScreen(connection, user);
    std::cout << "O ten lot chodziło?" << std::endl;
    std::string answer;
    std::cin >> answer;
    if(answer != "tak") {
        errorFunction("Nie wybrano lotu.", "Spróbuj ponownie.");
        return;
    }

    // wybieranie klasy biletu
    std::string ticketClass;
    std::cout << "Podaj klasę biletu: ";
    std::cin >> ticketClass;

    // wybieranie ilości biletów
    int ticketAmount;
    std::cout << "Podaj ilość biletów: ";
    std::cin >> ticketAmount;

    // sprawdzanie znizki uzytkownika
    double discount = user.getDiscount();
    double price = connection.getPrice();
    double totalPrice = price * ticketAmount;
    if(discount != 0) {
        totalPrice = totalPrice * discount;
    }
    std::cout << "Cena przed znizka: " << ticketAmount << " biletów: " << price * ticketAmount << std::endl;
    std::cout << "Cena po znizce: " << ticketAmount << " biletów: " << totalPrice << std::endl;

    // sprawdzanie czy uzytkownik ma karte premium o klasie platynowa
    std::string premiumCard = user.premiumCard;
    if(premiumCard == "platynowa") {
        std::cout << "Wyświetlanie samolotu i wybór miejsca" << std::endl;
    }
}

void handleBuyTicket(int choice, FlightConnection& flightConnection, User& user) {
    if(choice == 0) {
        handleSingleTicket(flightConnection, user);
    }
}

void handleTicketChoice(FlightConnection& connection, User& user) {
    int choice = CreateTicketMenu();
    std::cout << choice << std::endl;
    handleBuyTicket(choice, connection, user);
//    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateTicketScreen()));
//    ftxui::Render(screen, *CreateTicketScreen());
//    std::cout << screen.ToString() << '\0' << std::endl;
// TODO
}