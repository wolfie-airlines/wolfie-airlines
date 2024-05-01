#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>

#include "../../../user/User.h"
#include "../../FlightConnection.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

int CreateFlightChoiceScreen();
void CreateAllFlightsScreen(const std::vector<FlightConnection> &connections, User &user);
void CreateFoundFlightScreen(FlightConnection &connection, User &user);
std::string pageSizeString(int totalPages);

#endif  // FLIGHT_PRINT_FUNCTIONS_H
