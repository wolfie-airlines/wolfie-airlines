/**
 * @file user_profession_functions.h
 * @brief This file contains the declaration of user profession handling functions.
 */

#ifndef AIRPORT_USER_PROFESSION_FUNCTIONS_H
#define AIRPORT_USER_PROFESSION_FUNCTIONS_H

#include "../user.h"

/**
 * @brief Handles the profession choice of a user.
 * @param choice The choice made by the user.
 * @param user The user making the choice.
 */
void HandleProfessionChoice(int choice, User &user);

/**
 * @brief Handles the profession of a user.
 * @param user The user whose profession is being handled.
 */
void HandleProfession(User &user);

#endif  // AIRPORT_USER_PROFESSION_FUNCTIONS_H