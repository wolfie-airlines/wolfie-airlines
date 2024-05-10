#include "flight_functions.h"

#include <vector>

#include "../../functions/info_prints/info_prints.h"
#include "../../functions/main_prints/main_prints.h"
#include "flight_prints/flight_prints.h"

void HandleFlightSearchByCity(FlightConnection &flight_connection, User &user) {
    std::string departureCity = DisplayMessageAndCaptureStringInput("LOOK FOR CONNECTION", "Enter departure city: ");
    std::string destinationCity = DisplayMessageAndCaptureStringInput("LOOK FOR CONNECTION", "Enter desination city: ");

    FlightConnection connection = flight_connection.FindConnection(departureCity, destinationCity);

    if (connection.GetDepartureCity() == departureCity && connection.GetDestinationCity() == destinationCity) {
        CreateFoundFlightScreen(connection, user);
    } else {
        PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
    }
}

void HandleFlightSearchById(FlightConnection &flight_connection, User &user) {
    std::string flightId = DisplayMessageAndCaptureStringInput("LOOK FOR CONNECTION", "Enter flight ID: ");

    FlightConnection connection = flight_connection.FindConnectionById(flightId);

    if (connection.GetIdentifier() == flightId) {
        CreateFoundFlightScreen(connection, user);
    } else {
        PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
    }
}

void HandleFlightSearchByPrice(FlightConnection &flight_connection, User &user) {
    double minPrice = DisplayMessageAndCaptureDoubleInput("LOOK FOR CONNECTION", "Enter minimum price: ");
    double maxPrice = DisplayMessageAndCaptureDoubleInput("LOOK FOR CONNECTION", "Enter maximum price: ");

    std::vector<FlightConnection> connections = flight_connection.FindConnectionByPrice(minPrice, maxPrice);
    if (connections.empty()) {
        PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void HandleFlightSearchByDeparture(FlightConnection &flight_connection, User &user) {
    std::string departureCity = DisplayMessageAndCaptureStringInput("LOOK FOR CONNECTION", "Enter departure city: ");

    std::vector<FlightConnection> connections = flight_connection.FindConnectionsByDeparture(departureCity);
    if (connections.empty()) {
        PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void HandleFlightSearchByDestination(FlightConnection &flight_connection, User &user) {
    std::string destinationCity = DisplayMessageAndCaptureStringInput("LOOK FOR CONNECTION", "Enter destination city: ");

    std::vector<FlightConnection> connections = flight_connection.FindConnectionsByDestination(destinationCity);
    if (connections.empty()) {
        PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
    } else {
        if (connections.size() == 1) {
            CreateFoundFlightScreen(connections[0], user);
        } else {
            CreateAllFlightsScreen(connections, user);
        }
    }
}

void HandleFlightOptions(FlightConnection &flight_connection, User &user) {
    int answer = CreateFlightChoiceScreen();
    if (answer == 0) {
        std::vector<FlightConnection> connections = flight_connection.FindAllConnections();
        CreateAllFlightsScreen(connections, user);

    } else if (answer == 1) {
        HandleFlightSearchByCity(flight_connection, user);
    } else if (answer == 2) {
        HandleFlightSearchById(flight_connection, user);
    } else if (answer == 3) {
        HandleFlightSearchByPrice(flight_connection, user);
    } else if (answer == 4) {
        HandleFlightSearchByDeparture(flight_connection, user);
    } else if (answer == 5) {
        HandleFlightSearchByDestination(flight_connection, user);
    } else if (answer == 7) {
        return;
    } else {
        PrintErrorMessage("Invalid selection.", TRY_AGAIN);
    }
}