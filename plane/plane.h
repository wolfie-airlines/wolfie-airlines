/**
 * @file plane.h
 * @brief Ten plik zawiera deklarację funkcji ProcessSeatSelectionAndPurchase.
 */

#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

#include <vector>

#include "../flights/flight_connection.h"
#include "../user/user.h"

/**
 * @brief Przetwarza wybór miejsca i zakup dla lotu.
 * @param seat_number Wybrane numery miejsc.
 * @param flight_connection Połączenie lotnicze.
 * @param found_connection Znalezione połączenie lotnicze.
 * @param user Użytkownik dokonujący zakupu.
 */
void ProcessSeatSelectionAndPurchase(std::vector<int> seat_number,
                                     FlightConnection &flight_connection,
                                     FlightConnection &found_connection,
                                     User &user);

#endif  // AIRPORT_PLANE_H