#include "flight_functions.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../functions/info_prints/info_prints.h"
#include "../../functions/main_prints/main_prints.h"
#include "../flight_connection.h"
#include "flight_prints/flight_prints.h"

const std::string NO_FLIGHT_FOUND = "Nie znaleziono takiego lotu.";
const std::string TRY_AGAIN = "Spróbuj ponownie.";

void handleFlightSearchByCity(FlightConnection &flightConnection, User &user) {
  std::string departureCity = DisplayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto wylotu: ");
  std::string destinationCity = DisplayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto przylotu: ");

  FlightConnection connection = flightConnection.FindConnection(departureCity, destinationCity);

  if (connection.GetDepartureCity() == departureCity && connection.GetDestinationCity() == destinationCity) {
    CreateFoundFlightScreen(connection, user);
  } else {
    PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
  }
}

void handleFlightSearchById(FlightConnection &flightConnection, User &user) {
  std::string flightId = DisplayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj identyfikator lotu: ");

  FlightConnection connection = flightConnection.FindConnectionById(flightId);

  if (connection.GetIdentifier() == flightId) {
    CreateFoundFlightScreen(connection, user);
  } else {
    PrintErrorMessage(NO_FLIGHT_FOUND, TRY_AGAIN);
  }
}

void handleFlightSearchByPrice(FlightConnection &flightConnection, User &user) {
  double minPrice = DisplayMessageAndCaptureDoubleInput("SZUKAJ POŁĄCZENIA", "Podaj minimalną cenę: ");
  double maxPrice = DisplayMessageAndCaptureDoubleInput("SZUKAJ POŁĄCZENIA", "Podaj maksymalną cenę: ");

  std::vector<FlightConnection> connections = flightConnection.FindConnectionByPrice(minPrice, maxPrice);
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

void handleFlightSearchByDeparture(FlightConnection &flightConnection, User &user) {
  std::string departureCity = DisplayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto wylotu: ");

  std::vector<FlightConnection> connections = flightConnection.FindConnectionsByDeparture(departureCity);
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

void handleFlightSearchByDestination(FlightConnection &flightConnection, User &user) {
  std::string destinationCity = DisplayMessageAndCaptureStringInput("SZUKAJ POŁĄCZENIA", "Podaj miasto przylotu: ");

  std::vector<FlightConnection> connections = flightConnection.FindConnectionsByDestination(destinationCity);
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
    handleFlightSearchByCity(flight_connection, user);
  } else if (answer == 2) {
    handleFlightSearchById(flight_connection, user);
  } else if (answer == 3) {
    handleFlightSearchByPrice(flight_connection, user);
  } else if (answer == 4) {
    handleFlightSearchByDeparture(flight_connection, user);
  } else if (answer == 5) {
    handleFlightSearchByDestination(flight_connection, user);
  } else if (answer == 7) {
    return;
  } else {
    PrintErrorMessage("Nieprawidłowy wybór.", TRY_AGAIN);
  }
}