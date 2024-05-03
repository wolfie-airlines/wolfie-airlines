/**
 * @file main_prints.h
 * @brief This file contains the declaration of various display and input capture functions.
 */

#ifndef AIRPORT_MAIN_PRINTS_H
#define AIRPORT_MAIN_PRINTS_H

#include <memory>

#include "ftxui/dom/elements.hpp"
#include "../../user/user.h"

/**
 * @brief Prints a screen.
 * @param screen The screen to print.
 */
void PrintScreen(const std::shared_ptr<ftxui::Element> &screen);

/**
 * @brief Prints a full width screen.
 * @param container The container to print.
 */
void PrintFullWidthScreen(std::shared_ptr<ftxui::Node> container);

/**
 * @brief Prints a node screen.
 * @param container The container to print.
 */
void PrintNodeScreen(std::shared_ptr<ftxui::Node> container);

/**
 * @brief Displays a message and captures string input.
 * @param title_message The title of the message.
 * @param text_message The text of the message.
 * @return The captured string input.
 */
std::string DisplayMessageAndCaptureStringInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Displays a message and captures double input.
 * @param title_message The title of the message.
 * @param text_message The text of the message.
 * @return The captured double input.
 */
double DisplayMessageAndCaptureDoubleInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Displays a warning and captures input.
 * @param title_message The title of the message.
 * @param text_message The text of the message.
 * @return The captured input.
 */
std::string DisplayWarningAndCaptureInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Displays the user menu.
 * @param user The user for whom the menu is displayed.
 */
void DisplayUserMenu(User &user);

/**
 * @brief Displays the main menu.
 */
void DisplayMenu();

#endif  // AIRPORT_MAIN_PRINTS_H