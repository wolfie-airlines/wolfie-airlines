#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "../../user/user.h"

void validFunction(const std::string &titleMessage, const std::string &optionalMessage);
void errorFunction(const std::string &titleMessage, const std::string &optionalMessage);
void logoutFunction(User &user);
void seeyaFunction();

#endif  // FUNCTIONS_H
