#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../../FlightConnection.h"


int CreateFlightChoiceScreen();
void CreateAllFlightsScreen(const std::vector<FlightConnection>& connections);
void CreateFoundFlightScreen(FlightConnection& connection);
std::string pageSizeString(int totalPages);

#endif // FLIGHT_PRINT_FUNCTIONS_H
