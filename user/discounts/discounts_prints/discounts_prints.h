/**
 * @file discounts_prints.h
 * @brief This file contains the declaration of discount information display and validation functions.
 */

#ifndef AIRPORT_DISCOUNTS_PRINTS_H
#define AIRPORT_DISCOUNTS_PRINTS_H

#include <string>

/**
 * @brief Displays discount information.
 * @return A string containing the discount information.
 */
std::string DisplayDiscountInfo();

/**
 * @brief Validates a discount choice.
 * @param discount_choice The discount choice to validate.
 * @return True if the discount choice is valid, false otherwise.
 */
bool ValidDiscount(const std::string &discount_choice);

#endif  // AIRPORT_DISCOUNTS_PRINTS_H