#ifndef USER_PAYMENT_FUNCTIONS_H
#define USER_PAYMENT_FUNCTIONS_H

#include <iostream>

#include "../../user.h"

void HandlePaymentOption(User &user);
bool AuthenticatePayment(User &user, const std::string &payment_method, const std::string &title_message, int target_price);

#endif  // USER_PAYMENT_FUNCTIONS_H