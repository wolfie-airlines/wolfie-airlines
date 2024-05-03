#include <stdexcept>
#include "validators.h"

bool ValidateFlightId(const std::string &flight_id) {
  return !flight_id.empty() && flight_id.length() == 5;
}

bool ValidateCity(const std::string &city) {
  return !city.empty();
}

bool ValidateDate(const std::string &date) {
  return !date.empty() && date.length() == 10 && date[2] == '.' && date[5] == '.';
}

bool ValidateTime(const std::string &time) {
  return !time.empty() && time.length() == 5 && time[2] == ':';
}

bool ValidatePrice(const std::string &price) {
  try {
    int price_int = std::stoi(price);
    return price_int >= 0;
  } catch (std::invalid_argument &e) {
    return false;
  }
}

bool ValidateNonEmpty(const std::string &input) {
  return !input.empty();
}

bool ValidateSolution(const std::string &solution) {
  try {
    return std::stoi(solution) == std::stoi(solution);
  } catch (std::invalid_argument &e) {
    try {
      double solution_double = std::stod(solution);
      return solution_double == solution_double;
    } catch (std::invalid_argument &e) {
      return !solution.empty();
    }
  }
}