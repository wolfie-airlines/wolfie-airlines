#ifndef AIRPORT_PREMIUM_CARDS_PRINTS_H
#define AIRPORT_PREMIUM_CARDS_PRINTS_H

#include <string>

#include "../../user.h"

std::string DisplayPremiumCardInfo();
bool ValidCardPayment(User &user, int price);

#endif  // AIRPORT_PREMIUM_CARDS_PRINTS_H