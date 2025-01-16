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

    // kopiujący
    Flight(const Flight& other)
        : flight_id(other.flight_id), departure_city(other.departure_city), destination_city(other.destination_city),
          departure_time(other.departure_time), arrival_time(other.arrival_time), available_seats(other.available_seats), price(other.price) {}

    // przenoszący
    Flight(Flight&& other) noexcept
        : flight_id(std::move(other.flight_id)), departure_city(std::move(other.departure_city)), destination_city(std::move(other.destination_city)),
          departure_time(std::move(other.departure_time)), arrival_time(std::move(other.arrival_time)), available_seats(other.available_seats), price(other.price) {
        other.available_seats = 0;
        other.price = 0;
    }

    // kopiujący - przypisanie
    Flight& operator=(const Flight& other) {
        if (this == &other) return *this;
        flight_id = other.flight_id;
        departure_city = other.departure_city;
        destination_city = other.destination_city;
        departure_time = other.departure_time;
        arrival_time = other.arrival_time;
        available_seats = other.available_seats;
        price = other.price;
        return *this;
    }

    // przenoszący - przypisanie
    Flight& operator=(Flight&& other) noexcept {
        if (this == &other) return *this;
        flight_id = std::move(other.flight_id);
        departure_city = std::move(other.departure_city);
        destination_city = std::move(other.destination_city);
        departure_time = std::move(other.departure_time);
        arrival_time = std::move(other.arrival_time);
        available_seats = other.available_seats;
        price = other.price;
        other.available_seats = 0;
        other.price = 0;
        return *this;
    }
};

#endif //CUSTOM_FLIGHT_H