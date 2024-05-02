#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>

#include "../../../user/user.h"
#include "../../flight_connection.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

int CreateFlightChoiceScreen();
void CreateAllFlightsScreen(const std::vector<FlightConnection> &connections, User &user);
void CreateFoundFlightScreen(FlightConnection &connection, User &user);
std::string PageSizeString(int totalPages);

#endif  // FLIGHT_PRINT_FUNCTIONS_H
