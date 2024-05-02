#ifndef AIRPORT_AUTHPRINTHANDLER_H
#define AIRPORT_AUTHPRINTHANDLER_H

#include <string>
#include <tuple>

std::tuple<std::string, std::string, std::string, bool> RegisterUser();
std::tuple<std::string, std::string, bool> Login();

#endif  // AIRPORT_AUTHPRINTHANDLER_H
