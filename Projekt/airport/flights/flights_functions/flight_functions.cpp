#include <iostream>
#include <string>
#include <vector>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../FlightConnection.h"
#include "flight_functions.h"
#include "../../functions/printFunctions.h"
#include "flight_print_functions/flight_print_functions.h"

void handleFlightOptions(FlightConnection& flightConnection) {
    int answer = CreateFlightChoiceScreen();
    if (answer == 0) {
        //wszystkie możliwe loty
        std::vector<FlightConnection> connections = flightConnection.findAllConnections();
        auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateFlightsScreen(connections)));
        ftxui::Render(userScreen, *CreateFlightsScreen(connections));
        std::cout << userScreen.ToString() << '\0' << std::endl;

    } else if (answer == 1) {
        //wybór lotów
        std::string departureCity, destinationCity;
        std::cout << "Podaj miasto wylotu: ";
        std::cin >> departureCity;
        std::cout << "Podaj miasto przylotu: ";
        std::cin >> destinationCity;

        FlightConnection connection = flightConnection.findConnection(departureCity, destinationCity);

        std::cout << connection.getDepartureCity() << " -> " << connection.getDestinationCity() << " | " << connection.getDepartureTime() << " -> " << connection.getArrivalTime() << " | " << connection.getPrice() << std::endl;
        std::cout << departureCity << " -> " << destinationCity << std::endl;

        if (connection.getDepartureCity() == departureCity && connection.getDestinationCity() == destinationCity) {
            std::cout << connection.getDepartureCity() << " -> " << connection.getDestinationCity() << " | " << connection.getDepartureTime() << " -> " << connection.getArrivalTime() << " | " << connection.getPrice() << std::endl;
        } else {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        }
    } else if(answer == 3 ) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}
