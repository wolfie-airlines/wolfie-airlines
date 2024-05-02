#ifndef AIRPORT_DISCOUNTS_H
#define AIRPORT_DISCOUNTS_H

#include "../user.h"

double GetDiscount(std::string choice);
void HandleDiscountChoice(User &user, std::string choice);
void PrintDiscountCard(User &user);

#endif  // AIRPORT_DISCOUNTS_H
