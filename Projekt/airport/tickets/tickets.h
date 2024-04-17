#ifndef AIRPORT_TICKETS_H
#define AIRPORT_TICKETS_H

#include "../flights/FlightConnection.h"
#include "../user/User.h"

void handleTicketChoice(FlightConnection& connection, User& user);
void handleBuyTicket(int choice, FlightConnection& flightConnection, User& user);
void handleFlightById(FlightConnection& flightConnection, User& user);
void handleFlightByData(FlightConnection& flightConnection, User& user);
void processPurchase(
        FlightConnection& flightConnection,
        FlightConnection& foundConnection,
        User& user);
#endif //AIRPORT_TICKETS_H
