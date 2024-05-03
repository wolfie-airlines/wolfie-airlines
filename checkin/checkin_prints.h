/**
 * @file checkin_prints.h
 * @brief This file contains the declaration of functions used for check-in operations.
 */

#ifndef AIRPORT_CHECKIN_FUNCTIONS_H
#define AIRPORT_CHECKIN_FUNCTIONS_H

#include "../user/user.h"

/**
 * @brief Prints the check-in screen for a user.
 * @param user The user for whom the check-in screen is printed.
 */
void PrintCheckinScreen(User &user);

#endif  // AIRPORT_CHECKIN_FUNCTIONS_H