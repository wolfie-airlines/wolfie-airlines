/**
 * @file main_functions.h
 * @brief Ten plik zawiera deklarację funkcji ProcessChoice.
 */

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "../authentication/authentication.h"
#include "../flights/flight_connection.h"

/**
 * @brief Przetwarza wybór użytkownika.
 * @param is_logged_in Boolean wskazujący, czy użytkownik jest zalogowany.
 * @param auth Obiekt Authentication.
 * @param user Obiekt User.
 * @param flight_connection Obiekt FlightConnection.
 */
void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection);

#endif  // MAIN_FUNCTIONS_H