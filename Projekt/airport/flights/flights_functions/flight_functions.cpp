#include "flight_functions.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../functions/info_print_functions.h"
#include "../../functions/main_prints/main_prints.h"
#include "../FlightConnection.h"
#include "flight_prints/flight_print_functions.h"

const std::string NO_FLIGHT_FOUND = "Nie znaleziono takiego lotu.";
const std::string TRY_AGAIN = "Spróbuj ponownie.";

void handleFlightSearchByCity(FlightConnection& flightConnection, User& user) {
    std::string departureCity = displayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto wylotu: ");
    std::string destinationCity = displayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto przylotu: ");

    FlightConnection connection = flightConnection.findConnection(departureCity, destinationCity);

    if (connection.getDepartureCity() == departureCity && connection.getDestinationCity() == destinationCity) {
        CreateFoundFlightScreen(connection, user);
    } else {
        errorFunction(NO_FLIGHT_FOUND, TRY_AGAIN);
    }
}

void handleFlightSearchById(FlightConnection& flightConnection, User& user) {
    std::string flightId = displayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj identyfikator lotu: ");

    FlightConnection connection = flightConnection.findConnectionById(flightId);

    if (connection.getIdentifier() == flightId) {
        CreateFoundFlightScreen(connection, user);
    } else {
        errorFunction(NO_FLIGHT_FOUND, TRY_AGAIN);
    }
}

void handleFlightSearchByPrice(FlightConnection& flightConnection, User& user) {
    double minPrice = displayMessageAndCaptureDoubleInput("SZUKAJ POŁĄCZENIA", "Podaj minimalną cenę: ");
    double maxPrice = displayMessageAndCaptureDoubleInput("SZUKAJ POŁĄCZENIA", "Podaj maksymalną cenę: ");

    std::vector<FlightConnection> connections = flightConnection.findConnectionByPrice(minPrice, maxPrice);
    if (connections.empty()) {
        errorFunction(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void handleFlightSearchByDeparture(FlightConnection& flightConnection, User& user) {
    std::string departureCity = displayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto wylotu: ");

    std::vector<FlightConnection> connections = flightConnection.findConnectionsByDeparture(departureCity);
    if (connections.empty()) {
        errorFunction(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void handleFlightSearchByDestination(FlightConnection& flightConnection, User& user) {
    std::string destinationCity = displayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto przylotu: ");

    std::vector<FlightConnection> connections = flightConnection.findConnectionsByDestination(destinationCity);
    if (connections.empty()) {
        errorFunction(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void handleFlightOptions(FlightConnection& flightConnection, User& user) {
    int answer = CreateFlightChoiceScreen();
    if (answer == 0) {
        std::vector<FlightConnection> connections = flightConnection.findAllConnections();
        CreateAllFlightsScreen(connections, user);

    } else if (answer == 1) {
        handleFlightSearchByCity(flightConnection, user);
    } else if (answer == 2) {
        handleFlightSearchById(flightConnection, user);
    } else if (answer == 3) {
        handleFlightSearchByPrice(flightConnection, user);
    } else if (answer == 4) {
        handleFlightSearchByDeparture(flightConnection, user);
    } else if (answer == 5) {
        handleFlightSearchByDestination(flightConnection, user);
    } else if (answer == 7) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", TRY_AGAIN);
    }
}