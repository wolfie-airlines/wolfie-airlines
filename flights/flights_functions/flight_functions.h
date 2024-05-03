#ifndef FLIGHT_FUNCTIONS_H
#define FLIGHT_FUNCTIONS_H

#include <string>

#include "../../user/user.h"
#include "../flight_connection.h"

const std::string NO_FLIGHT_FOUND = "Nie znaleziono takiego lotu.";
const std::string TRY_AGAIN = "Spróbuj ponownie.";

void HandleFlightSearchByCity(FlightConnection &flight_connection, User &user);

void HandleFlightSearchById(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByPrice(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByDeparture(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByDestination(FlightConnection &flight_connection, User &user);

void HandleFlightOptions(FlightConnection &flight_connection, User &user);

#endif  // FLIGHT_FUNCTIONS_H