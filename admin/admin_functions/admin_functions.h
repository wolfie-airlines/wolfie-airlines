/**
 * @file admin_functions.h
 * @brief This file contains the declarations of functions used in the admin dashboard.
 */

#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_

#include "../../user/user.h"

/**
 * @brief Handles the admin dashboard.
 * @param admin The admin object.
 * @param user The user object.
 */
void HandleAdminDashboard(Admin &admin, User &user);

/**
 * @brief Processes the addition of a flight.
 * @return A string representing the result of the operation.
 */
std::string ProcessAddingFlight();

/**
 * @brief Captures user input with validation.
 * @param title The title of the input field.
 * @param message The message to display to the user.
 * @param validator A function to validate the input.
 * @return The captured input.
 */
std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

/**
 * @brief Captures a line of input with validation.
 * @param title The title of the input field.
 * @param message The message to display to the user.
 * @param validator A function to validate the input.
 * @return The captured input.
 */
std::string CaptureLineWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

/**
 * @brief Captures a boolean value with validation.
 * @param title The title of the input field.
 * @param message The message to display to the user.
 * @return An optional boolean value. If the input is valid, the value is the captured input. If the input is invalid, the value is std::nullopt.
 */
std::optional<bool> CaptureBoolWithValidation(const std::string &title, const std::string &message);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_