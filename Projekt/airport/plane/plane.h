#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

#include <vector>

#include "../flights/flight_connection.h"
#include "../user/user.h"

void ProcessSeatSelectionAndPurchase(std::vector<int> seats_taken,
                                     FlightConnection &flight_connection,
                                     FlightConnection &found_connection,
                                     User &user);

#endif  // AIRPORT_PLANE_H