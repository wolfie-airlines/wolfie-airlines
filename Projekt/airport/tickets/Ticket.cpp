#include "Ticket.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"

std::string Ticket::getTicketId() const {
    return _ticket_id;
}

FlightConnection & Ticket::getTicketFlight() const {
    return _flightConnection;
}

double Ticket::getTicketPrice() const {
    return _price;
}

User Ticket::getTicketUser() const {
    return _user;
}

void Ticket::saveTicket() {
    bsoncxx::document::value ticket_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ticket_id", _ticket_id),
            bsoncxx::builder::basic::kvp("flight_id", _flightConnection.getIdentifier()),
            bsoncxx::builder::basic::kvp("user_username", _user.getUsername()),
            bsoncxx::builder::basic::kvp("price", _price)
    );

    bsoncxx::document::view ticket_view = ticket_builder.view();
    _collection.insert_one(ticket_view);
}