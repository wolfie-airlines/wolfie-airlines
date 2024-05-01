#ifndef AIRPORT_AUTHPRINTHANDLER_H
#define AIRPORT_AUTHPRINTHANDLER_H

#include <string>
#include <tuple>

std::tuple<std::string, std::string, std::string, bool> registerUser();
std::tuple<std::string, std::string, bool> login();

#endif  // AIRPORT_AUTHPRINTHANDLER_H
