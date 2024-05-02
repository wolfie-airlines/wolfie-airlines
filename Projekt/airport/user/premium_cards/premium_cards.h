#ifndef AIRPORT_PREMIUM_CARDS_H
#define AIRPORT_PREMIUM_CARDS_H

#include "../user.h"

void HandlePremiumCard(User &user);
void HandleCardChoice(const std::string &card, int price, User &user);
double GetCardDiscount(const std::string &card);
std::string RecognizeDiscountCard(double discount);

#endif  // AIRPORT_PREMIUM_CARDS_H
