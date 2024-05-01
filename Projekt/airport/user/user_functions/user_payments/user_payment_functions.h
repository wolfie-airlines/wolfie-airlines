#ifndef USER_PAYMENT_FUNCTIONS_H
#define USER_PAYMENT_FUNCTIONS_H

#include <iostream>

#include "../../User.h"

void handlePaymentOption(User &user);
bool paymentAuth(User &user, const std::string &paymentMethod, const std::string &titleMessage, int targetPrice);

#endif  // USER_PAYMENT_FUNCTIONS_H