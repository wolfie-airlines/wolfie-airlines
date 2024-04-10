#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "../user/User.h"

std::tuple<std::string, std::string, bool> login();
std::tuple<std::string, std::string, std::string, bool> registerUser();
void validFunction(const std::string& titleMessage, const std::string& optionalMessage);
void errorFunction(const std::string& titleMessage, const std::string& optionalMessage);
void logoutFunction();
void seeyaFunction();

#endif // FUNCTIONS_H
