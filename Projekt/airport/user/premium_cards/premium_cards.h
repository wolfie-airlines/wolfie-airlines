#ifndef AIRPORT_PREMIUM_CARDS_H
#define AIRPORT_PREMIUM_CARDS_H

#include "../User.h"

void handlePremiumCard(User &user);
void handleCardChoice(const std::string &card, int price, User &user);
double getCardDiscount(const std::string &card);
std::string recognizeDiscountCard(double discount);

#endif  // AIRPORT_PREMIUM_CARDS_H
