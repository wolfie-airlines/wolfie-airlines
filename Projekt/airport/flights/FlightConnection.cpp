#include "FlightConnection.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include <future>

FlightConnection::FlightConnection(
        const std::string& flight_id,
        const std::string& departureCity,
        const std::string& destinationCity,
        const std::string& departureTime,
        const std::string& arrivalTime,
        double price
) : flight_id(flight_id), departureCity(departureCity), destinationCity(destinationCity), departureTime(departureTime), arrivalTime(arrivalTime), price(price)
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
            double flightPrice = view["price"].get_double().value;
            connections.emplace_back(flightId,depCity, destCity, depTime, arrTime, flightPrice);
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
        double flightPrice = view["price"].get_double().value;
        return FlightConnection{flightId, depCity, destCity, depTime, arrTime, flightPrice};
    }
    return FlightConnection{"", "", "", "", "", 0};
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
        double flightPrice = view["price"].get_double().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, flightPrice);
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
        double flightPrice = view["price"].get_double().value;
        return FlightConnection{flightId, depCity, destCity, depTime, arrTime, flightPrice};
    }
    return FlightConnection{"", "", "", "", "", 0};
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
        double flightPrice = view["price"].get_double().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, flightPrice);
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
        double flightPrice = view["price"].get_double().value;
        connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, flightPrice);
    }

    return connections;
}