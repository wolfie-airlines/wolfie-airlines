#include "plane_prints.h"
#include <iostream>

void printPlane(Plane& plane) {
    std::cout << "Samolot: " << plane.flight_id << std::endl;
    std::cout << "Liczba miejsc: " << plane.seats << std::endl;
    std::cout << "Dostępne miejsca: " << plane.availableSeats << std::endl;
    std::cout << "Miejsca awaryjne: " << plane.emergencySeats[0] << ", " << plane.emergencySeats[1] << ", " << plane.emergencySeats[2] << ", " << plane.emergencySeats[3] << std::endl;
}