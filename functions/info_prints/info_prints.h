/**
 * @file functions.h
 * @brief This file contains the declaration of various print functions.
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "../../user/user.h"

/**
 * @brief Prints a success message.
 * @param title_message The title of the message.
 * @param optional_message An optional message to display.
 */
void PrintSuccessMessage(const std::string &title_message, const std::string &optional_message);

/**
 * @brief Prints an error message.
 * @param title_message The title of the message.
 * @param optional_message An optional message to display.
 */
void PrintErrorMessage(const std::string &title_message, const std::string &optional_message);

/**
 * @brief Prints a logout message for a user.
 * @param user The user who is logging out.
 */
void PrintLogout(User &user);

/**
 * @brief Prints a goodbye message.
 */
void PrintSeeya();

#endif  // FUNCTIONS_H