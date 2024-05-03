#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_

#include <string>

bool ValidateFlightId(const std::string &flight_id);
bool ValidateCity(const std::string &city);
bool ValidateDate(const std::string &date);
bool ValidateTime(const std::string &time);
bool ValidatePrice(const std::string &price);
bool ValidateNonEmpty(const std::string &input);
bool ValidateSolution(const std::string &solution);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_VALIDATORS_H_
