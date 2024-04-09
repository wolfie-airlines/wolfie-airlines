#ifndef AIRPORT_DISCOUNTS_H
#define AIRPORT_DISCOUNTS_H


#include "../User.h"

double getDiscount(int choice);
void handleDiscountChoice(User& user, int choice);
void handleDiscountCard(User& user);


#endif //AIRPORT_DISCOUNTS_H
