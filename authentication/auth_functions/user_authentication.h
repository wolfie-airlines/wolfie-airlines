#ifndef AIRPORT_AUTHPRINTHANDLER_H
#define AIRPORT_AUTHPRINTHANDLER_H

#include <string>
#include <tuple>
#include "../../user/user.h"
#include "../authentication.h"

std::tuple<std::string, std::string, std::string, bool> RegisterUser();
std::tuple<std::string, std::string, bool> Login();
void HandleRegistration(Authentication &auth);
bool HandleLogin(Authentication &auth, User &user);

#endif  // AIRPORT_AUTHPRINTHANDLER_H
