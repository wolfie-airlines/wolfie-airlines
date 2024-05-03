/**
 * @file premium_cards.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących karty premium.
 */

#ifndef AIRPORT_PREMIUM_CARDS_H
#define AIRPORT_PREMIUM_CARDS_H

#include "../user.h"

/**
 * @brief Obsługuje kartę premium użytkownika.
 * @param user Użytkownik z kartą premium.
 */
void HandlePremiumCard(User &user);

/**
 * @brief Obsługuje wybór karty przez użytkownika.
 * @param card Karta wybrana przez użytkownika.
 * @param price Cena karty.
 * @param user Użytkownik dokonujący wyboru.
 */
void HandleCardChoice(const std::string &card, int price, User &user);

/**
 * @brief Pobiera zniżkę z karty.
 * @param card Karta, dla której pobierana jest zniżka.
 * @return Zniżka jako double.
 */
double GetCardDiscount(const std::string &card);

/**
 * @brief Rozpoznaje kartę zniżkową na podstawie zniżki.
 * @param discount Zniżka do rozpoznania karty.
 * @return Rozpoznana karta jako string.
 */
std::string RecognizeDiscountCard(double discount);

#endif  // AIRPORT_PREMIUM_CARDS_H