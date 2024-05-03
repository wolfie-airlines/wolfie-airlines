/**
 * @file admin_prints.h
 * @brief This file contains the declarations of functions used for displaying admin related information.
 */

#ifndef AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_
#define AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_

/**
 * @brief Displays the admin menu.
 */
void DisplayAdminMenu();

/**
 * @brief Displays information related to adding a flight.
 */
void DisplayAddingFlightInfo();

/**
 * @brief Displays a message to the admin and captures their input.
 * @param title_message The title of the message.
 * @param text_message The text of the message.
 * @return The input captured from the admin.
 */
std::string DisplayAdminMessageAndCaptureInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Displays a message to the admin and captures a line of their input.
 * @param title_message The title of the message.
 * @param text_message The text of the message.
 * @return The line of input captured from the admin.
 */
std::string DisplayAdminMessageAndCaptureLine(const std::string &title_message, const std::string &text_message);

/**
 * @brief Displays the manage users menu.
 */
void DisplayManageUsersMenu();

#endif //AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_