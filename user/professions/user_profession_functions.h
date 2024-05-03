/**
 * @file user_profession_functions.h
 * @brief Ten plik zawiera deklaracje funkcji obsługujących zawód użytkownika.
 */

#ifndef AIRPORT_USER_PROFESSION_FUNCTIONS_H
#define AIRPORT_USER_PROFESSION_FUNCTIONS_H

#include "../user.h"

/**
 * @brief Obsługuje wybór zawodu przez użytkownika.
 * @param choice Wybór dokonany przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void HandleProfessionChoice(int choice, User &user);

/**
 * @brief Obsługuje zawód użytkownika.
 * @param user Użytkownik, którego zawód jest obsługiwany.
 */
void HandleProfession(User &user);

#endif  // AIRPORT_USER_PROFESSION_FUNCTIONS_H