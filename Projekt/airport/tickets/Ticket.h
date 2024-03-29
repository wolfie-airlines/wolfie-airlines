#ifndef AIRPORT_TICKET_H
#define AIRPORT_TICKET_H


#include <string>
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "../flights/FlightConnection.h"
#include "../user/User.h"

class Ticket {
private:
    std::string _ticket_id;
    FlightConnection& _flightConnection;
    double _price{};
    User& _user;
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
public:
    Ticket(const std::string &uri_str, const std::string &db_name, const std::string &collection_name,
           FlightConnection& flightConnection, User &user, double price)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]},
              _flightConnection(flightConnection), _user(user), _price(price) {}

    std::string getTicketId() const;
    FlightConnection & getTicketFlight() const;
    double getTicketPrice() const;
    User getTicketUser() const;
    void saveTicket();
};

#endif //AIRPORT_TICKET_H
