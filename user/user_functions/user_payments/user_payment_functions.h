/**
 * @file user_payment_functions.h
 * @brief This file contains the declaration of user payment handling functions.
 */

#ifndef USER_PAYMENT_FUNCTIONS_H
#define USER_PAYMENT_FUNCTIONS_H

#include <iostream>

#include "../../user.h"

/**
 * @brief Handles the payment option of a user.
 * @param user The user making the payment.
 */
void HandlePaymentOption(User &user);

/**
 * @brief Authenticates a payment made by a user.
 * @param user The user making the payment.
 * @param payment_method The method of payment used by the user.
 * @param title_message The title message for the payment.
 * @param target_price The target price of the payment.
 * @return True if the payment is authenticated, false otherwise.
 */
bool AuthenticatePayment(User &user, const std::string &payment_method, const std::string &title_message, int target_price);

#endif  // USER_PAYMENT_FUNCTIONS_H