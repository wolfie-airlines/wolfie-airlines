#ifndef AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
#define AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../user.h"

const int PAGE_SIZE = 4;

struct FlightInfo {
  int flight_number;
  std::string flight_id;
  std::string departure;
  std::string destination;
  std::string departure_time;
  double price;
  std::vector<int> seats;
  bool checkin;
  bool luggage_checkin;
};

std::optional<std::string> CreateTicketsScreen(User &user, bool is_checkin = false);

#endif  // AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
