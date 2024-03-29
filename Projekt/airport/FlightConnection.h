#pragma once

#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/collection.hpp>

class FlightConnection {
private:
    std::string departureCity;
    std::string destinationTime;
    std::string arrivalTime;
    std::string departureTime;
    std::string destinationCity;
    double price{};

    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
public:
    FlightConnection(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

FlightConnection(
        const std::string& departureCity,
        const std::string& destinationCity,
        const std::string& departureTime,
        const std::string& arrivalTime,
        double price
);

    std::string getDepartureCity() const;
    std::string getDestinationCity() const;
    std::string getDepartureTime() const;
    std::string getArrivalTime() const;
    double getPrice() const;
    std::vector<FlightConnection> findAllConnections();
    FlightConnection findConnection(const std::string &departureCity, const std::string &destinationCity);


};
