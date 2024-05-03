/**
 * @file user_print_functions.h
 * @brief Ten plik zawiera deklaracje funkcji wyświetlania interfejsu użytkownika.
 */

#ifndef AIRPORT_USER_PRINT_FUNCTIONS_H
#define AIRPORT_USER_PRINT_FUNCTIONS_H

#include <string>

#include "../../user.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

/**
 * @brief Wyświetla menu ustawień dla użytkownika.
 * @param user Użytkownik, dla którego wyświetlane jest menu ustawień.
 * @return Ciąg znaków reprezentujący menu ustawień.
 */
std::string DisplaySettingsMenu(const User &user);

/**
 * @brief Wyświetla domyślny ekran płatności.
 * @return Liczba całkowita reprezentująca status operacji.
 */
int DisplayDefaultPaymentScreen();

/**
 * @brief Wyświetla ekran profilu dla użytkownika.
 * @param user Użytkownik, dla którego wyświetlany jest ekran profilu.
 */
void DisplayProfileScreen(User &user);

#endif  // AIRPORT_USER_PRINT_FUNCTIONS_H