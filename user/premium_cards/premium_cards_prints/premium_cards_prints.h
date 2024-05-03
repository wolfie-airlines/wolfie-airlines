/**
 * @file premium_cards_prints.h
 * @brief Ten plik zawiera deklaracje funkcji wyświetlania informacji o karcie premium i walidacji płatności kartą.
 */

#ifndef AIRPORT_PREMIUM_CARDS_PRINTS_H
#define AIRPORT_PREMIUM_CARDS_PRINTS_H

#include <string>

#include "../../user.h"

/**
 * @brief Wyświetla informacje o karcie premium.
 * @return Ciąg znaków zawierający informacje o karcie premium.
 */
std::string DisplayPremiumCardInfo();

/**
 * @brief Waliduje płatność kartą.
 * @param user Użytkownik dokonujący płatności.
 * @param price Cena płatności.
 * @return Prawda, jeśli płatność kartą jest prawidłowa, w przeciwnym razie fałsz.
 */
bool ValidCardPayment(User &user, int price);

#endif  // AIRPORT_PREMIUM_CARDS_PRINTS_H