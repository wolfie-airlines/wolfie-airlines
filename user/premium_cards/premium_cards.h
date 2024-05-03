/**
 * @file premium_cards.h
 * @brief This file contains the declaration of various premium card handling functions.
 */

#ifndef AIRPORT_PREMIUM_CARDS_H
#define AIRPORT_PREMIUM_CARDS_H

#include "../user.h"

/**
 * @brief Handles the premium card of a user.
 * @param user The user with the premium card.
 */
void HandlePremiumCard(User &user);

/**
 * @brief Handles the card choice of a user.
 * @param card The card chosen by the user.
 * @param price The price of the card.
 * @param user The user making the choice.
 */
void HandleCardChoice(const std::string &card, int price, User &user);

/**
 * @brief Gets the discount of a card.
 * @param card The card to get the discount for.
 * @return The discount as a double.
 */
double GetCardDiscount(const std::string &card);

/**
 * @brief Recognizes a discount card based on a discount.
 * @param discount The discount to recognize the card from.
 * @return The recognized card as a string.
 */
std::string RecognizeDiscountCard(double discount);

#endif  // AIRPORT_PREMIUM_CARDS_H