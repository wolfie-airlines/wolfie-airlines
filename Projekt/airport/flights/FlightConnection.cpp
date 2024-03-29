#include "FlightConnection.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"

FlightConnection::FlightConnection(
        const std::string& departureCity,
        const std::string& destinationCity,
        const std::string& departureTime,
        const std::string& arrivalTime,
        double price
) : departureCity(departureCity), destinationCity(destinationCity), departureTime(departureTime), arrivalTime(arrivalTime), price(price)
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
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        price = view["price"].get_double().value;
        connections.emplace_back(depCity, destCity, depTime, arrTime, price);
    }

    return connections;
}

FlightConnection FlightConnection::findConnection(const std::string& _departureCity, const std::string& _destinationCity) {

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("departureCity", departureCity),
            bsoncxx::builder::basic::kvp("destinationCity", destinationCity),
            bsoncxx::builder::basic::kvp("departureTime", departureTime),
            bsoncxx::builder::basic::kvp("arrivalTime", arrivalTime)
    );
    bsoncxx::document::view filter_view = filter_builder.view();

    mongocxx::cursor cursor = _collection.find(filter_view);
    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        double price = view["price"].get_double().value;
        return FlightConnection{depCity, destCity, depTime, arrTime, price};
    }
    return FlightConnection{"", "", "", "", 0};
}
