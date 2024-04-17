#pragma once

#include <string>
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"

class FlightConnection {
private:
    std::string flight_id;
    std::string departureCity;
    std::string destinationTime;
    std::string arrivalTime;
    std::string departureTime;
    std::string destinationCity;
    int availableSeats{};
    double price{};

    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;

public:
    FlightConnection(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

FlightConnection(
        std::string flight_id,
        std::string  departureCity,
        std::string  destinationCity,
        std::string  departureTime,
        std::string  arrivalTime,
        int availableSeats,
        double price
);

    [[nodiscard]] std::string getDepartureCity() const;
    [[nodiscard]] std::string getDestinationCity() const;
    [[nodiscard]] std::string getDepartureTime() const;
    [[nodiscard]] std::string getArrivalTime() const;
    [[nodiscard]] std::string getIdentifier() const;
    [[nodiscard]] int getAvailableSeats() const;
    [[nodiscard]] double getPrice() const;
    std::vector<FlightConnection> findAllConnections();
    FlightConnection findConnection(const std::string &departureCity, const std::string &destinationCity);
    std::vector<FlightConnection> findConnectionByPrice(double &minPrice, double &maxPrice);
    FlightConnection findConnectionById(const std::string& id);
    std::vector<FlightConnection> findConnectionsByDeparture(const std::string &departureCity);
    std::vector<FlightConnection> findConnectionsByDestination(const std::string &destinationCity);
    std::vector<int> getSeatsTaken(const std::string &flight_identifier);
    void updateSeatsTaken(const std::string& flight_identifier, const std::vector<int> &seatsTaken);
};
