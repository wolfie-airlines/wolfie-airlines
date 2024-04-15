#include "FlightConnection.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "../functions/info_print_functions.h"
#include <future>
#include <utility>

FlightConnection::FlightConnection(
        std::string  flight_id,
        std::string  departureCity,
        std::string  destinationCity,
        std::string  departureTime,
        std::string  arrivalTime,
        int availableSeats,
        double price
) : flight_id(std::move(flight_id)), departureCity(std::move(departureCity)), destinationCity(std::move(destinationCity)), departureTime(std::move(departureTime)), arrivalTime(std::move(arrivalTime)), availableSeats(availableSeats), price(price)
{}

std::string FlightConnection::getDepartureCity() const {
    return departureCity;
}

std::string FlightConnection::getDestinationCity() const {
    return destinationCity;
}

std::string FlightConnection::getDepartureTime() const {
    return departureTime;
}

std::string FlightConnection::getArrivalTime() const {
    return arrivalTime;
}

std::string FlightConnection::getIdentifier() const {
    return flight_id;
}

double FlightConnection::getPrice() const {
    return price;
}

int FlightConnection::getAvailableSeats() const {
    return availableSeats;
}

std::vector<FlightConnection> FlightConnection::findAllConnections() {
    std::vector<FlightConnection> connections;

        bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document();

        bsoncxx::document::view filter_view = filter_builder.view();

        mongocxx::cursor cursor = _collection.find(filter_view);
        for (auto&& doc : cursor) {
            bsoncxx::document::view view = doc;
            auto flightId = (std::string) view["identifier"].get_string().value;
            auto depCity = (std::string) view["departureCity"].get_string().value;
            auto destCity = (std::string) view["destinationCity"].get_string().value;
            auto depTime = (std::string) view["departureTime"].get_string().value;
            auto arrTime = (std::string) view["arrivalTime"].get_string().value;
            auto avSeats = view["availableSeats"].get_int32().value;
            double flightPrice = view["price"].get_int32().value;
            connections.emplace_back(flightId,depCity, destCity, depTime, arrTime, avSeats, flightPrice);
        }
    return connections;
}

FlightConnection FlightConnection::findConnection(const std::string& departCity, const std::string& destinCity) {

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("departureCity", departCity),
            bsoncxx::builder::basic::kvp("destinationCity", destinCity)
    );
    bsoncxx::document::view filter_view = filter_builder.view();

    mongocxx::cursor cursor = _collection.find(filter_view);
    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        auto avSeats = view["availableSeats"].get_int32().value;
        double flightPrice = view["price"].get_double().value;
        return FlightConnection{flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice};
    }
    return FlightConnection{"", "", "", "", "",0, 0};
}

std::vector<FlightConnection> FlightConnection::findConnectionByPrice(double &minPrice, double &maxPrice) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("price", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("$gte", minPrice),
                    bsoncxx::builder::basic::kvp("$lte", maxPrice)
            ))
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    std::vector<FlightConnection> connections;

    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        auto avSeats = view["availableSeats"].get_int32().value;
        double flightPrice = view["price"].get_double().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
    }

    return connections;
}

FlightConnection FlightConnection::findConnectionById(const std::string& id) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("identifier", id)
    );

    bsoncxx::document::view filter_view = filter_builder.view();

    mongocxx::cursor cursor = _collection.find(filter_view);
    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        auto avSeats = view["availableSeats"].get_int32().value;
        double flightPrice = view["price"].get_int32().value;
        return FlightConnection{flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice};
    }
    return FlightConnection{"", "", "", "", "",0, 0};
}


std::vector<FlightConnection> FlightConnection::findConnectionsByDeparture(const std::string &departCity) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("departureCity", departCity)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    std::vector<FlightConnection> connections;

    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        auto avSeats = view["availableSeats"].get_int32().value;
        double flightPrice = view["price"].get_double().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
    }

    return connections;
}

std::vector<FlightConnection> FlightConnection::findConnectionsByDestination(const std::string &destinCity) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("destinationCity", destinCity)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    std::vector<FlightConnection> connections;

    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        double flightPrice = view["price"].get_int32().value;
        auto avSeats = view["availableSeats"].get_int32().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
    }

    return connections;
}

std::vector<int> FlightConnection::getSeatsTaken(const std::string& flight_identifier) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("identifier", flight_identifier)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    std::vector<int> seatsTaken;

    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto seats = view["seatsTaken"].get_array().value;
        for (auto&& seat : seats) {
            seatsTaken.push_back(seat.get_int32().value);
        }
    }

    return seatsTaken;
}

void FlightConnection::updateSeatsTaken(const std::string& flight_identifier, const std::vector<int> &seatsTaken) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("identifier", flight_identifier)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    std::vector<int> oldSeatsTaken;
    int avSeats{};
    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto seats = view["seatsTaken"].get_array().value;
        avSeats = view["availableSeats"].get_int32().value;
        for (auto&& seat : seats) {
            oldSeatsTaken.push_back(seat.get_int32().value);
        }
    }

    for (auto&& seat : seatsTaken) {
        if (std::find(oldSeatsTaken.begin(), oldSeatsTaken.end(), seat) != oldSeatsTaken.end()) {
            errorFunction("Miejsce " + std::to_string(seat) + " jest już zajęte.", "Wybierz inne miejsce.");
            return;
        }
        oldSeatsTaken.push_back(seat);
    }

    bsoncxx::builder::basic::array array_builder{};
    for (const auto& seat : oldSeatsTaken) {
        array_builder.append(seat);
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("seatsTaken", array_builder),
                    bsoncxx::builder::basic::kvp("availableSeats", avSeats - (int) seatsTaken.size())
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view, update_view);

    validFunction("Bilet został zakupiony pomyślnie.", "Dziękujemy za zakup biletu. Możesz zobaczyć go w zakładce 'Moje bilety'.");
}