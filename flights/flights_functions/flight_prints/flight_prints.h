/**
 * @file flight_prints.h
 * @brief This file contains the declaration of functions used for flight operations.
 */

#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>

#include "../../../user/user.h"
#include "../../flight_connection.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

const int PAGE_SIZE = 9; ///< The size of the page.

/**
 * @brief Creates a flight choice screen.
 * @return An integer representing the choice made.
 */
int CreateFlightChoiceScreen();

/**
 * @brief Creates a screen displaying all flights.
 * @param connections The vector of flight connections.
 * @param user The user for whom the screen is created.
 */
void CreateAllFlightsScreen(const std::vector<FlightConnection> &connections, User &user);

/**
 * @brief Creates a screen displaying a found flight.
 * @param connection The flight connection to display.
 * @param user The user for whom the screen is created.
 */
void CreateFoundFlightScreen(FlightConnection &connection, User &user);

/**
 * @brief Creates a string representing the page size.
 * @param totalPages The total number of pages.
 * @return A string representing the page size.
 */
std::string PageSizeString(int totalPages);

#endif  // FLIGHT_PRINT_FUNCTIONS_H