/**
 * @file flight_functions.h
 * @brief This file contains the declaration of functions used for flight operations.
 */

#ifndef FLIGHT_FUNCTIONS_H
#define FLIGHT_FUNCTIONS_H

#include <string>

#include "../../user/user.h"
#include "../flight_connection.h"

const std::string NO_FLIGHT_FOUND = "No such flight was found.";  ///< Message displayed when no flight is found.
const std::string TRY_AGAIN = "Try again.";                       ///< Message prompting the user to try again.

/**
 * @brief Handles flight search by city.
 * @param flight_connection The flight connection to search.
 * @param user The user performing the search.
 */
void HandleFlightSearchByCity(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles flight search by ID.
 * @param flight_connection The flight connection to search.
 * @param user The user performing the search.
 */
void HandleFlightSearchById(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles flight search by price.
 * @param flight_connection The flight connection to search.
 * @param user The user performing the search.
 */
void HandleFlightSearchByPrice(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles flight search by departure.
 * @param flight_connection The flight connection to search.
 * @param user The user performing the search.
 */
void HandleFlightSearchByDeparture(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles flight search by destination.
 * @param flight_connection The flight connection to search.
 * @param user The user performing the search.
 */
void HandleFlightSearchByDestination(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles flight options.
 * @param flight_connection The flight connection to handle.
 * @param user The user choosing the options.
 */
void HandleFlightOptions(FlightConnection &flight_connection, User &user);

#endif  // FLIGHT_FUNCTIONS_H