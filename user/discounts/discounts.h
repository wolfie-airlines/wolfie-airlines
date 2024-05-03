/**
 * @file discounts.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących zniżki.
 */

#ifndef AIRPORT_DISCOUNTS_H
#define AIRPORT_DISCOUNTS_H

#include "../user.h"

/**
 * @brief Pobiera zniżkę na podstawie wyboru.
 * @param choice Wybór użytkownika.
 * @return Zniżka jako double.
 */
double GetDiscount(std::string choice);

/**
 * @brief Obsługuje wybór zniżki przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 * @param choice Wybór użytkownika.
 */
void HandleDiscountChoice(User &user, std::string choice);

/**
 * @brief Drukuje kartę zniżkową dla użytkownika.
 * @param user Użytkownik, dla którego drukowana jest karta zniżkowa.
 */
void PrintDiscountCard(User &user);

#endif  // AIRPORT_DISCOUNTS_H