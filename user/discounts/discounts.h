/**
 * @file discounts.h
 * @brief This file contains the declaration of various discount handling functions.
 */

#ifndef AIRPORT_DISCOUNTS_H
#define AIRPORT_DISCOUNTS_H

#include "../user.h"

/**
 * @brief Gets the discount based on a choice.
 * @param choice The choice of the user.
 * @return The discount as a double.
 */
double GetDiscount(std::string choice);

/**
 * @brief Handles the discount choice of a user.
 * @param user The user making the choice.
 * @param choice The choice of the user.
 */
void HandleDiscountChoice(User &user, std::string choice);

/**
 * @brief Prints a discount card for a user.
 * @param user The user for whom the discount card is printed.
 */
void PrintDiscountCard(User &user);

#endif  // AIRPORT_DISCOUNTS_H