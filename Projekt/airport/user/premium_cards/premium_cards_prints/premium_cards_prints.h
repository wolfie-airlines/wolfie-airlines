#ifndef AIRPORT_PREMIUM_CARDS_PRINTS_H
#define AIRPORT_PREMIUM_CARDS_PRINTS_H

#include <string>
#include "../../User.h"

std::string displayPremiumCardInfo();
bool validCardPayment(User& user, int price);

#endif //AIRPORT_PREMIUM_CARDS_PRINTS_H