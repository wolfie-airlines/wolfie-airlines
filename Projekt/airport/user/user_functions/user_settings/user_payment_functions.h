#ifndef USER_PAYMENT_FUNCTIONS_H
#define USER_PAYMENT_FUNCTIONS_H


#include "../../User.h"
#include <iostream>

void handlePaymentOption(User& user);
bool paymentAuth(User& user, const std::string& paymentMethod, const std::string& titleMessage, int targetPrice);

#endif // USER_PAYMENT_FUNCTIONS_H