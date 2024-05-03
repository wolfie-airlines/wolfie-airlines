/**
 * @file user_tickets_print_functions.h
 * @brief Ten plik zawiera deklaracje funkcji drukowania biletów użytkownika.
 */

#ifndef AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
#define AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../user.h"

/// @brief Liczba elementów na stronie na ekranie biletów.
const int PAGE_SIZE = 4;

/**
 * @struct FlightInfo
 * @brief Zawiera informacje o locie.
 */
struct FlightInfo {
  int flight_number; ///< Numer lotu.
  std::string flight_id; ///< ID lotu.
  std::string departure; ///< Miejsce odlotu.
  std::string destination; ///< Miejsce docelowe.
  std::string departure_time; ///< Czas odlotu.
  double price; ///< Cena lotu.
  std::vector<int> seats; ///< Miejsca w locie.
  bool checkin; ///< Czy użytkownik odprawił się.
  bool luggage_checkin; ///< Czy użytkownik odprawił bagaż.
};

/**
 * @brief Tworzy ekran biletów dla użytkownika.
 * @param user Użytkownik, dla którego tworzony jest ekran biletów.
 * @param is_checkin Czy użytkownik jest w trakcie odprawy.
 * @return Ciąg znaków reprezentujący ekran biletów, lub nullopt, jeśli operacja się nie powiedzie.
 */
std::optional<std::string> CreateTicketsScreen(User &user, bool is_checkin = false);

#endif  // AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H