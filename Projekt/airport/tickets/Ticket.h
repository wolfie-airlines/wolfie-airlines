#ifndef AIRPORT_TICKET_H
#define AIRPORT_TICKET_H


#include <string>
#include <utility>
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "../flights/FlightConnection.h"
#include "../user/User.h"

class Ticket {
private:
    std::string ticketId;
    std::shared_ptr<FlightConnection> flightConnection; // Zmieniony typ na shared_ptr
    double price{};
    User user;

    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;

public:
    Ticket(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
            : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

    Ticket(
            std::string  ticketId,
            const std::shared_ptr<FlightConnection>& flightConnection,
            double price,
            User  user,
            const std::string& uri_str,
            const std::string& db_name,
            const std::string& collection_name
    ) : ticketId(std::move(ticketId)), flightConnection(flightConnection), price(price), user(std::move(user)),
        _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

    std::string getTicketId();
    std::shared_ptr<FlightConnection> getTicketFlight();
    double getTicketPrice() const {};
    User getTicketUser() const {};

    void saveTicket();
};

#endif //AIRPORT_TICKET_H
