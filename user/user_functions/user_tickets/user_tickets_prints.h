/**
 * @file user_tickets_print_functions.h
 * @brief This file contains the declaration of user ticket printing functions.
 */

#ifndef AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
#define AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../user.h"

/// @brief The number of items per page in the ticket screen.
const int PAGE_SIZE = 4;

/**
 * @struct FlightInfo
 * @brief Contains information about a flight.
 */
struct FlightInfo {
  int flight_number; ///< The flight number.
  std::string flight_id; ///< The flight ID.
  std::string departure; ///< The departure location.
  std::string destination; ///< The destination location.
  std::string departure_time; ///< The departure time.
  double price; ///< The price of the flight.
  std::vector<int> seats; ///< The seats in the flight.
  bool checkin; ///< Whether the user has checked in.
  bool luggage_checkin; ///< Whether the user has checked in luggage.
};

/**
 * @brief Creates the tickets screen for a user.
 * @param user The user for whom the tickets screen is created.
 * @param is_checkin Whether the user is checking in.
 * @return A string representing the tickets screen, or nullopt if the operation fails.
 */
std::optional<std::string> CreateTicketsScreen(User &user, bool is_checkin = false);

#endif  // AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H