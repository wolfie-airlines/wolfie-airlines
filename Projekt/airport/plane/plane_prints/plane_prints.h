#ifndef AIRPORT_PLANE_PRINTS_H
#define AIRPORT_PLANE_PRINTS_H

#include <vector>
#include "../../flights/FlightConnection.h"

void printPlane();
bool testPrint(std::vector<int> seatsTaken, FlightConnection& flightConnection);

#endif //AIRPORT_PLANE_PRINTS_H