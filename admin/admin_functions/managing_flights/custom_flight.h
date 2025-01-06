#ifndef CUSTOM_FLIGHT_H
#define CUSTOM_FLIGHT_H

#include <string>

class Flight {
public:
    std::string flight_id;
    std::string departure_city;
    std::string destination_city;
    std::string departure_time;
    std::string arrival_time;
    int available_seats{};
    int price{};

    Flight() = default;
    Flight(std::string id, std::string dep_city, std::string dest_city, std::string dep_time, std::string arr_time, int seats, int pr)
        : flight_id(std::move(id)), departure_city(std::move(dep_city)), destination_city(std::move(dest_city)),
          departure_time(std::move(dep_time)), arrival_time(std::move(arr_time)), available_seats(seats), price(pr) {}

    Flight(const Flight& other) = default;
    Flight(Flight&& other) noexcept = default;
    Flight& operator=(const Flight& other) = default;
    Flight& operator=(Flight&& other) noexcept = default;
};

#endif //CUSTOM_FLIGHT_H
