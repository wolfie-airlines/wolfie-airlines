#ifndef AIRPORT_TICKET_H
#define AIRPORT_TICKET_H

#include <string>
#include <vector>
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "../user/User.h"

class Ticket {
private:
    std::string ticketId;
    std::string flightId;
    double price{};
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
    User passenger{_client};
public:
    Ticket(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

    Ticket(
            std::string ticketId,
            User passenger,
            std::string flightId,
            double price
    );

    std::string getTicketId() const;
    std::string getPassengerUsername() const;
    std::string getFlightId() const;
    double getPrice() const;

};


#endif //AIRPORT_TICKET_H
