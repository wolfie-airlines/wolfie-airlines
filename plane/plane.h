/**
 * @file plane.h
 * @brief This file contains the declaration of the ProcessSeatSelectionAndPurchase function.
 */

#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

#include <vector>

#include "../flights/flight_connection.h"
#include "../user/user.h"

/**
 * @brief Processes the seat selection and purchase for a flight.
 * @param seat_number The seat numbers selected.
 * @param flight_connection The flight connection.
 * @param found_connection The found flight connection.
 * @param user The user making the purchase.
 */
void ProcessSeatSelectionAndPurchase(std::vector<int> seat_number,
                                     FlightConnection &flight_connection,
                                     FlightConnection &found_connection,
                                     User &user);

#endif  // AIRPORT_PLANE_H