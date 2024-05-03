/**
 * @file main_functions.h
 * @brief This file contains the declaration of the ProcessChoice function.
 */

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "../authentication/authentication.h"
#include "../flights/flight_connection.h"

/**
 * @brief Processes the user's choice.
 * @param is_logged_in A boolean indicating if the user is logged in.
 * @param auth The Authentication object.
 * @param user The User object.
 * @param flight_connection The FlightConnection object.
 */
void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection);

#endif  // MAIN_FUNCTIONS_H