#ifndef AIRPORT_HELPERS_H
#define AIRPORT_HELPERS_H
#include <string>

std::string extractFileName(const std::string &path);
void countdown(int seconds, const std::string &type);
std::string hashString(const std::string &stringToHash);

#endif  // AIRPORT_HELPERS_H
