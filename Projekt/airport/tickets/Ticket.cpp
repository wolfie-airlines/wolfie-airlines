#include "Ticket.h"
#include "bsoncxx/json.hpp"
#include <utility>

Ticket::Ticket(
        std::string  ticketId,
        User passenger,
        std::string  flightId,
        double price
) : ticketId(std::move(ticketId)), passenger(std::move(passenger)), flightId(std::move(flightId)), price(price)
{}

std::string Ticket::getTicketId() const {
    return ticketId;
}

std::string Ticket::getPassengerUsername() const {
    return passenger.username;
}

std::string Ticket::getFlightId() const {
    return flightId;
}

double Ticket::getPrice() const {
    return price;
}