/**
 * @file validators.h
 * @brief Ten plik zawiera deklaracje funkcji walidacyjnych używanych w panelu administratora.
 */

#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_

#include <string>

/**
 * @brief Waliduje ID lotu.
 * @param flight_id ID lotu do zweryfikowania.
 * @return Prawda, jeśli ID lotu jest prawidłowe, w przeciwnym razie fałsz.
 */
bool ValidateFlightId(const std::string &flight_id);

/**
 * @brief Waliduje nazwę miasta.
 * @param city Nazwa miasta do zweryfikowania.
 * @return Prawda, jeśli nazwa miasta jest prawidłowa, w przeciwnym razie fałsz.
 */
bool ValidateCity(const std::string &city);

/**
 * @brief Waliduje datę.
 * @param date Data do zweryfikowania.
 * @return Prawda, jeśli data jest prawidłowa, w przeciwnym razie fałsz.
 */
bool ValidateDate(const std::string &date);

/**
 * @brief Waliduje czas.
 * @param time Czas do zweryfikowania.
 * @return Prawda, jeśli czas jest prawidłowy, w przeciwnym razie fałsz.
 */
bool ValidateTime(const std::string &time);

/**
 * @brief Waliduje cenę.
 * @param price Cena do zweryfikowania.
 * @return Prawda, jeśli cena jest prawidłowa, w przeciwnym razie fałsz.
 */
bool ValidatePrice(const std::string &price);

/**
 * @brief Waliduje, czy dane wejściowe nie są puste.
 * @param input Dane wejściowe do zweryfikowania.
 * @return Prawda, jeśli dane wejściowe nie są puste, w przeciwnym razie fałsz.
 */
bool ValidateNonEmpty(const std::string &input);

/**
 * @brief Waliduje rozwiązanie.
 * @param solution Rozwiązanie do zweryfikowania.
 * @return Prawda, jeśli rozwiązanie jest prawidłowe, w przeciwnym razie fałsz.
 */
bool ValidateSolution(const std::string &solution);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_