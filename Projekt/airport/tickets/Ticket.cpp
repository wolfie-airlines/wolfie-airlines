#include "Ticket.h"

#include <utility>
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"

Ticket::Ticket(
        mongocxx::client _client,
        std::string ticketId,
        std::shared_ptr<FlightConnection> &flightConnection,
        double price,
        User user,
        const mongocxx::client &client,
        const std::string &db_name,
        const std::string &collection_name
) : ticketId(std::move(ticketId)), flightConnection(flightConnection), price(price), user(std::move(user)),
    _client(client), _db(_client[db_name]), _collection(_db[collection_name]) {}

std::string Ticket::getTicketId()  {
    return ticketId;
}

std::shared_ptr<FlightConnection> Ticket::getTicketFlight() {
    return flightConnection;
}

double Ticket::getTicketPrice() const {
    return price;
}

User Ticket::getTicketUser() const {
    return user;
}

void Ticket::saveTicket() {
    // Implementacja zapisu biletu do bazy danych
    bsoncxx::builder::stream::document document{};

    document << "ticketId" << ticketId
             << "price" << price
             << "user" << bsoncxx::types::b_utf8{user.getUsername()}; // Zakładając, że getUsername() zwraca nazwę użytkownika

    bsoncxx::document::value doc_value = document.extract();

    _collection.insert_one(std::move(doc_value));
}
