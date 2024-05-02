#ifndef AIRPORT_TICKETS_H
#define AIRPORT_TICKETS_H

#include "../flights/flight_connection.h"
#include "../user/user.h"

void HandleTicketChoice(FlightConnection &flight_connection, User &user);
void HandleBuyTicket(int choice, FlightConnection &flight_connection, User &user);
void HandleFlightById(FlightConnection &flight_connection, User &user);
void HandleFlightByData(FlightConnection &flight_connection, User &user);
void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user);
#endif  // AIRPORT_TICKETS_H
