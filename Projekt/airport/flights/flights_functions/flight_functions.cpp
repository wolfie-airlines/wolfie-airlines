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
        //szukanie po mieście wylotu - mieście przylotu
        std::string departureCity, destinationCity;
        std::cout << "Podaj miasto wylotu: ";
        std::cin >> departureCity;
        std::cout << "Podaj miasto przylotu: ";
        std::cin >> destinationCity;

        FlightConnection connection = flightConnection.findConnection(departureCity, destinationCity);

        if (connection.getDepartureCity() == departureCity && connection.getDestinationCity() == destinationCity) {
           CreateFoundFlightScreen(connection);
        } else {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        }
    } else if (answer == 2) {
        //szukanie po mieście wylotu - mieście przylotu
        std::string flightId;
        std::cout << "Podaj identyfikator lotu: ";
        std::cin >> flightId;

        FlightConnection connection = flightConnection.findConnectionById(flightId);

        if (connection.getIdentifier() == flightId) {
            CreateFoundFlightScreen(connection);
        } else {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        }
    } else if (answer == 3) {
        //szukanie po cenie
        double minPrice, maxPrice;
        std::cout << "Podaj minimalną kwotę: ";
        std::cin >> minPrice;
        std::cout << "Podaj maksymalną kwotę: ";
        std::cin >> maxPrice;

        std::vector<FlightConnection> connections = flightConnection.findConnectionByPrice(minPrice, maxPrice);
        if(connections.empty()) {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        } else {
            if(connections.size() == 1) {
                CreateFoundFlightScreen(connections[0]);
            } else {
                CreateAllFlightsScreen(connections);
            }
        }

    } else if (answer == 4) {
        //szukanie po mieście wylotu - zwraca wszystkie loty z tego miasta (1 lbu wiecej)
        std::string departureCity;
        std::cout << "Podaj miasto wylotu: ";
        std::cin >> departureCity;

        std::vector<FlightConnection> connections = flightConnection.findConnectionsByDeparture(departureCity);
        if(connections.empty()) {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        } else {
            if(connections.size() == 1) {
                CreateFoundFlightScreen(connections[0]);
            } else {
                CreateAllFlightsScreen(connections);
            }
        }

    } else if (answer == 5) {
        //szukanie po mieście przylotu - zwraca wszystkie loty do tego miasta (wektor)
        std::string destinationCity;
        std::cout << "Podaj miasto przylotu: ";
        std::cin >> destinationCity;

        std::vector<FlightConnection> connections = flightConnection.findConnectionsByDestination(destinationCity);
        if(connections.empty()) {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        } else {
            if(connections.size() == 1) {
                CreateFoundFlightScreen(connections[0]);
            } else {
                CreateAllFlightsScreen(connections);
            }
        }

    }

    else if(answer == 7 ) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}
