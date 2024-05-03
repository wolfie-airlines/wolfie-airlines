/**
 * @file luggage_handler.h
 * @brief Ten plik zawiera deklarację funkcji CheckIn.
 */

#ifndef AIRPORT_LUGGAGEHANDLER_H
#define AIRPORT_LUGGAGEHANDLER_H

#include "../user/user.h"

/**
 * @brief Przeprowadza odprawę użytkownika na konkretny lot.
 * @param user Użytkownik do odprawy.
 * @param flightNumber Numer lotu, na który odprawiany jest użytkownik.
 */
void CheckIn(User &user, int flightNumber);

#endif  // AIRPORT_LUGGAGEHANDLER_H