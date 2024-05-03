/**
 * @file user_settings_functions.h
 * @brief Ten plik zawiera deklaracje funkcji obsługujących opcje ustawień użytkownika.
 */

#ifndef USER_SETTINGS_FUNCTIONS_H
#define USER_SETTINGS_FUNCTIONS_H

#include <iostream>

#include "../../user.h"

/**
 * @brief Obsługuje opcję ustawień użytkownika.
 * @param user Użytkownik, którego opcja ustawień jest obsługiwana.
 */
void HandleSettingsOption(User &user);

#endif  // USER_SETTINGS_FUNCTIONS_H