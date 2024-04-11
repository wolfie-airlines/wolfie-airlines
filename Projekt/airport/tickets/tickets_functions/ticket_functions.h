#ifndef AIRPORT_TICKET_FUNCTIONS_H
#define AIRPORT_TICKET_FUNCTIONS_H

#include "../../flights/FlightConnection.h"
#include "../../user/User.h"

void handleTicketChoice(FlightConnection& connection, User& user);
void handleBuyTicket(int choice, FlightConnection& flightConnection, User& user);
void handleSingleTicket(FlightConnection& flightConnection, User& user);
#endif //AIRPORT_TICKET_FUNCTIONS_H
