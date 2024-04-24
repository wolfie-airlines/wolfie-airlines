#ifndef TICKETS_PRINT_FUNCTIONS_H
#define TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>
#include "../../flights/FlightConnection.h"
#include "../../user/User.h"

int CreateTicketMenu();
bool validChoice(const std::string& choiceTitle, const std::string& choiceText);
std::string displayMessageAndCaptureInput(const std::string& titleMessage, const std::string& textMessage);
std::string displayWarningAndCaptureInput(const std::string& titleMessage, const std::string& textMessage);
void druknijFakturke(User& user, FlightConnection& foundConnection, const std::vector<int>& selectedSeats);
void openWebsite();

#endif // TICKETS_PRINT_FUNCTIONS_H
