#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../../FlightConnection.h"


int CreateFlightChoiceScreen();
std::shared_ptr<ftxui::Element> CreateFlightsScreen(const std::vector<FlightConnection>& connections);

#endif // FLIGHT_PRINT_FUNCTIONS_H
