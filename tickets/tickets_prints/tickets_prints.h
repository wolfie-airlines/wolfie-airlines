#ifndef TICKETS_PRINT_FUNCTIONS_H
#define TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../flights/flight_connection.h"
#include "../../user/user.h"

int CreateTicketMenu();
bool ValidChoice(const std::string &choice_title, const std::string &choice_text);
void PrintTicketInvoice(User &user, FlightConnection &found_connection, const std::vector<int> &selected_seats);
void OpenWebsite();

#endif  // TICKETS_PRINT_FUNCTIONS_H
