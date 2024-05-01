#ifndef AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
#define AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../User.h"

struct FlightInfo {
    int flightNumber;
    std::string flightId;
    std::string departure;
    std::string destination;
    std::string departureTime;
    double price;
    std::vector<int> seats;
    bool checkin;
    bool luggageCheckin;
};

std::optional<std::string> createTicketsScreen(User& user, bool isCheckin = false);

#endif  // AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
