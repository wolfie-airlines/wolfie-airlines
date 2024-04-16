#ifndef TICKETS_PRINT_FUNCTIONS_H
#define TICKETS_PRINT_FUNCTIONS_H

#include <string>

int CreateTicketMenu();
bool validChoice(const std::string& choiceTitle, const std::string& choiceText);
std::string displayMessageAndCaptureInput(const std::string& titleMessage, const std::string& textMessage);

#endif // TICKETS_PRINT_FUNCTIONS_H
