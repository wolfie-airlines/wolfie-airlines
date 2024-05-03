/**
 * @file luggage_handler.h
 * @brief This file contains the declaration of the CheckIn function.
 */

#ifndef AIRPORT_LUGGAGEHANDLER_H
#define AIRPORT_LUGGAGEHANDLER_H

#include "../user/user.h"

/**
 * @brief Checks in a user for a specific flight.
 * @param user The user to check in.
 * @param flightNumber The number of the flight the user is checking in for.
 */
void CheckIn(User &user, int flightNumber);

#endif  // AIRPORT_LUGGAGEHANDLER_H