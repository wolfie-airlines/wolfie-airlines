/**
 * @file flight_functions.h
 * @brief Ten plik zawiera deklaracje funkcji używanych do operacji lotniczych.
 */

#ifndef FLIGHT_FUNCTIONS_H
#define FLIGHT_FUNCTIONS_H

#include <string>

#include "../../user/user.h"
#include "../flight_connection.h"

const std::string NO_FLIGHT_FOUND = "Nie znaleziono takiego lotu."; ///< Wiadomość wyświetlana, gdy nie znaleziono lotu.
const std::string TRY_AGAIN = "Spróbuj ponownie."; ///< Wiadomość zachęcająca użytkownika do ponownej próby.

/**
 * @brief Obsługuje wyszukiwanie lotów według miasta.
 * @param flight_connection Połączenie lotnicze do wyszukania.
 * @param user Użytkownik wykonujący wyszukiwanie.
 */
void HandleFlightSearchByCity(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje wyszukiwanie lotów według ID.
 * @param flight_connection Połączenie lotnicze do wyszukania.
 * @param user Użytkownik wykonujący wyszukiwanie.
 */
void HandleFlightSearchById(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje wyszukiwanie lotów według ceny.
 * @param flight_connection Połączenie lotnicze do wyszukania.
 * @param user Użytkownik wykonujący wyszukiwanie.
 */
void HandleFlightSearchByPrice(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje wyszukiwanie lotów według miejsca odlotu.
 * @param flight_connection Połączenie lotnicze do wyszukania.
 * @param user Użytkownik wykonujący wyszukiwanie.
 */
void HandleFlightSearchByDeparture(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje wyszukiwanie lotów według miejsca docelowego.
 * @param flight_connection Połączenie lotnicze do wyszukania.
 * @param user Użytkownik wykonujący wyszukiwanie.
 */
void HandleFlightSearchByDestination(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje opcje lotu.
 * @param flight_connection Połączenie lotnicze do obsłużenia.
 * @param user Użytkownik wybierający opcje.
 */
void HandleFlightOptions(FlightConnection &flight_connection, User &user);

#endif  // FLIGHT_FUNCTIONS_H