/**
 * @file premium_cards_prints.h
 * @brief This file contains the declaration of premium card information display and validation functions.
 */

#ifndef AIRPORT_PREMIUM_CARDS_PRINTS_H
#define AIRPORT_PREMIUM_CARDS_PRINTS_H

#include <string>

#include "../../user.h"

/**
 * @brief Displays premium card information.
 * @return A string containing the premium card information.
 */
std::string DisplayPremiumCardInfo();

/**
 * @brief Validates a card payment.
 * @param user The user making the payment.
 * @param price The price of the payment.
 * @return True if the card payment is valid, false otherwise.
 */
bool ValidCardPayment(User &user, int price);

#endif  // AIRPORT_PREMIUM_CARDS_PRINTS_H