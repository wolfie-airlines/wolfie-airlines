#ifndef AIRPORT_PREMIUM_CARDS_H
#define AIRPORT_PREMIUM_CARDS_H


#include "../User.h"

void handlePremiumCard(User& user);
void handleCardChoice(const std::string& card, int price, User& user);
void setPremiumCard(User& user, const std::string& card);


#endif //AIRPORT_PREMIUM_CARDS_H
