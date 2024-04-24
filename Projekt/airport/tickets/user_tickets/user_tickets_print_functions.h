#ifndef AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
#define AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H

#include "../../user/User.h"
#include <string>
#include <vector>

struct FlightInfo {
    int flightNumber;
    std::string flightId;
    std::string departure;
    std::string destination;
    std::string departureTime;
    double price;
    std::vector<int> seats;
    bool checkin;
};

void createTicketsScreen(User& user);

#endif //AIRPORT_USER_TICKETS_PRINT_FUNCTIONS_H
