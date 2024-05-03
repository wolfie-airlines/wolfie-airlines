/**
 * @file user_payment_functions.h
 * @brief Ten plik zawiera deklaracje funkcji obsługujących płatności użytkownika.
 */

#ifndef USER_PAYMENT_FUNCTIONS_H
#define USER_PAYMENT_FUNCTIONS_H

#include <iostream>

#include "../../user.h"

/**
 * @brief Obsługuje opcję płatności użytkownika.
 * @param user Użytkownik dokonujący płatności.
 */
void HandlePaymentOption(User &user);

/**
 * @brief Autentykuje płatność dokonaną przez użytkownika.
 * @param user Użytkownik dokonujący płatności.
 * @param payment_method Metoda płatności używana przez użytkownika.
 * @param title_message Tytuł wiadomości dla płatności.
 * @param target_price Docelowa cena płatności.
 * @return Prawda, jeśli płatność jest uwierzytelniona, w przeciwnym razie fałsz.
 */
bool AuthenticatePayment(User &user, const std::string &payment_method, const std::string &title_message, int target_price);

#endif  // USER_PAYMENT_FUNCTIONS_H