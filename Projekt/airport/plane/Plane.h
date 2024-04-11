#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H

#pragma once

#include <string>
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "../flights/FlightConnection.h"

class Plane {
private:
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
public:

    Plane(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}
    std::string flight_id;
    int seats;
    int availableSeats;
    int emergencySeats[4];
    Plane(
            const std::string &flight_id,
            int seats,
            int availableSeats,
            int emergencySeats[4]
    );

    mongocxx::collection getCollection() const;
    Plane getPlane(FlightConnection& connection) const;
    void printPlane();
};



#endif //AIRPORT_PLANE_H
