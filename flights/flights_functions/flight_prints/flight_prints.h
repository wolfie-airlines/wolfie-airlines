/**
 * @file flight_prints.h
 * @brief Ten plik zawiera deklaracje funkcji używanych do operacji lotniczych.
 */

#ifndef FLIGHT_PRINT_FUNCTIONS_H
#define FLIGHT_PRINT_FUNCTIONS_H

#include <string>

#include "../../../user/user.h"
#include "../../flight_connection.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

const int PAGE_SIZE = 9; ///< Rozmiar strony.

/**
 * @brief Tworzy ekran wyboru lotu.
 * @return Liczba całkowita reprezentująca dokonany wybór.
 */
int CreateFlightChoiceScreen();

/**
 * @brief Tworzy ekran wyświetlający wszystkie loty.
 * @param connections Wektor połączeń lotniczych.
 * @param user Użytkownik, dla którego tworzony jest ekran.
 */
void CreateAllFlightsScreen(const std::vector<FlightConnection> &connections, User &user);

/**
 * @brief Tworzy ekran wyświetlający znaleziony lot.
 * @param connection Połączenie lotnicze do wyświetlenia.
 * @param user Użytkownik, dla którego tworzony jest ekran.
 */
void CreateFoundFlightScreen(FlightConnection &connection, User &user);

/**
 * @brief Tworzy ciąg reprezentujący rozmiar strony.
 * @param totalPages Całkowita liczba stron.
 * @return Ciąg reprezentujący rozmiar strony.
 */
std::string PageSizeString(int totalPages);

#endif  // FLIGHT_PRINT_FUNCTIONS_H