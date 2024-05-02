#ifndef FLIGHT_FUNCTIONS_H
#define FLIGHT_FUNCTIONS_H

#include "../../user/user.h"
#include "../flight_connection.h"

void HandleFlightSearchByCity(FlightConnection &flight_connection, User &user);

void HandleFlightSearchById(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByPrice(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByDeparture(FlightConnection &flight_connection, User &user);

void HandleFlightSearchByDestination(FlightConnection &flight_connection, User &user);

void HandleFlightOptions(FlightConnection &flight_connection, User &user);

#endif  // FLIGHT_FUNCTIONS_H