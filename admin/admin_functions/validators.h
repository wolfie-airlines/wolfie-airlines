/**
 * @file validators.h
 * @brief This file contains the declarations of validation functions used in the admin dashboard.
 */

#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_

#include <string>

/**
 * @brief Validates a flight ID.
 * @param flight_id The flight ID to validate.
 * @return True if the flight ID is valid, false otherwise.
 */
bool ValidateFlightId(const std::string &flight_id);

/**
 * @brief Validates a city name.
 * @param city The city name to validate.
 * @return True if the city name is valid, false otherwise.
 */
bool ValidateCity(const std::string &city);

/**
 * @brief Validates a date.
 * @param date The date to validate.
 * @return True if the date is valid, false otherwise.
 */
bool ValidateDate(const std::string &date);

/**
 * @brief Validates a time.
 * @param time The time to validate.
 * @return True if the time is valid, false otherwise.
 */
bool ValidateTime(const std::string &time);

/**
 * @brief Validates a price.
 * @param price The price to validate.
 * @return True if the price is valid, false otherwise.
 */
bool ValidatePrice(const std::string &price);

/**
 * @brief Validates that an input is not empty.
 * @param input The input to validate.
 * @return True if the input is not empty, false otherwise.
 */
bool ValidateNonEmpty(const std::string &input);

/**
 * @brief Validates a solution.
 * @param solution The solution to validate.
 * @return True if the solution is valid, false otherwise.
 */
bool ValidateSolution(const std::string &solution);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_