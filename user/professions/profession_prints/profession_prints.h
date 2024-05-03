/**
 * @file profession_prints.h
 * @brief This file contains the declaration of profession information display and validation functions.
 */

#ifndef AIRPORT_PROFESSION_PRINTS_H
#define AIRPORT_PROFESSION_PRINTS_H

#include <string>

#include "../../user.h"

/**
 * @brief Creates a profession screen.
 * @return An integer representing the status of the operation.
 */
int CreateProfessionScreen();

/**
 * @brief Displays profession information.
 * @return A string containing the profession information.
 */
std::string DisplayProfessionInfo();

/**
 * @brief Handles an invalid answer.
 */
void InvalidAnswer();

/**
 * @brief Handles a valid answer.
 * @param category The category of the answer.
 * @param user The user providing the answer.
 */
void ValidAnswer(const std::string &category, User &user);

#endif  // AIRPORT_PROFESSION_PRINTS_H