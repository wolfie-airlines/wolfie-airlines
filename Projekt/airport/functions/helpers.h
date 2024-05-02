#ifndef AIRPORT_HELPERS_H
#define AIRPORT_HELPERS_H
#include <string>

std::string ExtractFileName(const std::string &path);
void Countdown(int seconds, const std::string &type);
std::string HashString(const std::string &string_to_hash);

#endif  // AIRPORT_HELPERS_H
