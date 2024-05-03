/**
 * @file checkin_prints.h
 * @brief Ten plik zawiera deklaracje funkcji używanych do operacji check-in.
 */

#ifndef AIRPORT_CHECKIN_FUNCTIONS_H
#define AIRPORT_CHECKIN_FUNCTIONS_H

#include "../user/user.h"

/**
 * @brief Wyświetla ekran check-in dla użytkownika.
 * @param user Użytkownik, dla którego wyświetlany jest ekran check-in.
 */
void PrintCheckinScreen(User &user);

#endif  // AIRPORT_CHECKIN_FUNCTIONS_H