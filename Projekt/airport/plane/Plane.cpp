#include "Plane.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include <future>


Plane::Plane(const std::string &flight_id, int seats, int availableSeats, int *emergencySeats) {}

mongocxx::collection Plane::getCollection() const {
    return _collection;
}

Plane Plane::getPlane(FlightConnection& connection) const {
    std::string flightId = connection.getIdentifier();
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("identifier", connection.getIdentifier())
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = getCollection().find(filter_view);

    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flight_identifier = (std::string) view["identifier"].get_string().value;
        int planeSeats = view["seats"].get_int32().value;
        int availSeats = view["availableSeats"].get_int32().value;
        int emergSeats[4] = {
                view["emergencySeats"].get_array().value[0].get_int32().value,
                view["emergencySeats"].get_array().value[1].get_int32().value,
                view["emergencySeats"].get_array().value[2].get_int32().value,
                view["emergencySeats"].get_array().value[3].get_int32().value
        };
        return Plane(flight_identifier, planeSeats, availSeats, emergSeats);
    }

    return Plane("", 0, 0, new int[4]);
}

void Plane::printPlane() {
    std::cout << "Samolot: " << flight_id << std::endl;
    std::cout << "Liczba miejsc: " << seats << std::endl;
    std::cout << "Dostępne miejsca: " << availableSeats << std::endl;
    std::cout << "Miejsca awaryjne: " << emergencySeats[0] << ", " << emergencySeats[1] << ", " << emergencySeats[2] << ", " << emergencySeats[3] << std::endl;
}
