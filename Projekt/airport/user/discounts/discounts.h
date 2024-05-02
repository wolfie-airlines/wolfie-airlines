#ifndef AIRPORT_DISCOUNTS_H
#define AIRPORT_DISCOUNTS_H

#include "../user.h"

double GetDiscount(int choice);
void HandleDiscountChoice(User &user, int choice);
void PrintDiscountCard(User &user);

#endif  // AIRPORT_DISCOUNTS_H
