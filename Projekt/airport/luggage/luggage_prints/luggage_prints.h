#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H


#include "../../user/User.h"
#include "../item/Item.h"

void welcomeInLuggageCheckin(User& user);
void printAllItems(User& user);
void printSpecificItem(Item& item);

#endif //AIRPORT_LUGGAGE_PRINTS_H
