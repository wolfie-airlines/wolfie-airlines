#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

#include <vector>

#include "../flights/FlightConnection.h"
#include "../user/User.h"

void processSeatSelectionAndPurchase(std::vector<int> seatsTaken,
                                     FlightConnection& flightConnection,
                                     FlightConnection& foundConnection,
                                     User& user);

#endif  // AIRPORT_PLANE_H