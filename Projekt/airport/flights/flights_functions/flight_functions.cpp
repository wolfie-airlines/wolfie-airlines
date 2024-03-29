#include <iostream>
#include <string>
#include <vector>
#include "../FlightConnection.h"
#include "flight_functions.h"
#include "../../functions/printFunctions.h"
#include "flight_print_functions/flight_print_functions.h"

void handleFlightOptions(FlightConnection& flightConnection) {
    int answer = CreateFlightChoiceScreen();
    if (answer == 0) {
        //wszystkie możliwe loty
        std::vector<FlightConnection> connections = flightConnection.findAllConnections();
        CreateAllFlightsScreen(connections);

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
           CreateFoundFlightScreen(connection);
        } else {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        }
    } else if (answer == 3) {
        //wybór lotów
        double minPrice, maxPrice;
        std::cout << "Podaj minimalną kwotę: ";
        std::cin >> minPrice;
        std::cout << "Podaj maksymalną kwotę: ";
        std::cin >> maxPrice;

        std::vector<FlightConnection> connections = flightConnection.findConnectionByPrice(minPrice, maxPrice);
        CreateAllFlightsScreen(connections);

    } else if(answer == 7 ) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}
