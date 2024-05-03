/**
 * @file discounts_prints.h
 * @brief Ten plik zawiera deklaracje funkcji wyświetlania i walidacji informacji o zniżkach.
 */

#ifndef AIRPORT_DISCOUNTS_PRINTS_H
#define AIRPORT_DISCOUNTS_PRINTS_H

#include <string>

/**
 * @brief Wyświetla informacje o zniżkach.
 * @return Ciąg znaków zawierający informacje o zniżkach.
 */
std::string DisplayDiscountInfo();

/**
 * @brief Waliduje wybór zniżki.
 * @param discount_choice Wybór zniżki do zweryfikowania.
 * @return Prawda, jeśli wybór zniżki jest prawidłowy, w przeciwnym razie fałsz.
 */
bool ValidDiscount(const std::string &discount_choice);

#endif  // AIRPORT_DISCOUNTS_PRINTS_H