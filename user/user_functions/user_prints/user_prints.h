/**
 * @file user_print_functions.h
 * @brief This file contains the declaration of user interface display functions.
 */

#ifndef AIRPORT_USER_PRINT_FUNCTIONS_H
#define AIRPORT_USER_PRINT_FUNCTIONS_H

#include <string>

#include "../../user.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

/**
 * @brief Displays the settings menu for a user.
 * @param user The user for whom the settings menu is displayed.
 * @return A string representing the settings menu.
 */
std::string DisplaySettingsMenu(const User &user);

/**
 * @brief Displays the default payment screen.
 * @return An integer representing the status of the operation.
 */
int DisplayDefaultPaymentScreen();

/**
 * @brief Displays the profile screen for a user.
 * @param user The user for whom the profile screen is displayed.
 */
void DisplayProfileScreen(User &user);

#endif  // AIRPORT_USER_PRINT_FUNCTIONS_H