#include "flight_connection.h"

#include <future>
#include <utility>

#include "../functions/info_prints/info_prints.h"
#include "bsoncxx/json.hpp"
#include "mongocxx/v_noabi/mongocxx/client.hpp"

FlightConnection::FlightConnection(
    std::string flight_id,
    std::string departure_city,
    std::string destination_city,
    std::string departure_time,
    std::string arrival_time,
    int available_seats,
    double price)
    : _flight_id_(std::move(flight_id)),
      _departureCity_(std::move(departure_city)),
      _destinationCity_(std::move(destination_city)),
      _departureTime_(std::move(departure_time)),
      _arrivalTime_(std::move(arrival_time)),
      _availableSeats_(available_seats),
      _price_(price) {}

std::string FlightConnection::GetDepartureCity() const {
  return _departureCity_;
}

std::string FlightConnection::GetDestinationCity() const {
  return _destinationCity_;
}

std::string FlightConnection::GetDepartureTime() const {
  return _departureTime_;
}

std::string FlightConnection::GetArrivalTime() const {
  return _arrivalTime_;
}

std::string FlightConnection::GetIdentifier() const {
  return _flight_id_;
}

double FlightConnection::GetPrice() const {
  return _price_;
}

int FlightConnection::GetAvailableSeats() const {
  return _availableSeats_;
}

std::vector<FlightConnection> FlightConnection::FindAllConnections() {
  std::vector<FlightConnection> connections;

  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document();

  bsoncxx::document::view filter_view = filter_builder.view();

  mongocxx::cursor cursor = _collection_.find(filter_view);
  for (auto &&doc : cursor) {
    bsoncxx::document::view view = doc;
    auto flightId = (std::string) view["identifier"].get_string().value;
    auto depCity = (std::string) view["departureCity"].get_string().value;
    auto destCity = (std::string) view["destinationCity"].get_string().value;
    auto depTime = (std::string) view["departureTime"].get_string().value;
    auto arrTime = (std::string) view["arrivalTime"].get_string().value;
    auto avSeats = view["availableSeats"].get_int32().value;
    double flightPrice = view["price"].get_int32().value;
    connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
  }
  return connections;
}

FlightConnection FlightConnection::FindConnection(const std::string &departure_city, const std::string &destination_city) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("departureCity", departure_city),
      bsoncxx::builder::basic::kvp("destinationCity", destination_city));
  bsoncxx::document::view filter_view = filter_builder.view();

  mongocxx::cursor cursor = _collection_.find(filter_view);
  for (auto &&doc : cursor) {
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
  return FlightConnection{"", "", "", "", "", 0, 0};
}

std::vector<FlightConnection> FlightConnection::FindConnectionByPrice(double &min_price, double &max_price) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("price", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("$gte", min_price),
          bsoncxx::builder::basic::kvp("$lte", max_price))));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  std::vector<FlightConnection> connections;

  for (auto &&doc : cursor) {
    bsoncxx::document::view view = doc;
    auto flightId = (std::string) view["identifier"].get_string().value;
    auto depCity = (std::string) view["departureCity"].get_string().value;
    auto destCity = (std::string) view["destinationCity"].get_string().value;
    auto depTime = (std::string) view["departureTime"].get_string().value;
    auto arrTime = (std::string) view["arrivalTime"].get_string().value;
    auto avSeats = view["availableSeats"].get_int32().value;
    double flightPrice = view["price"].get_int32().value;
    connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
  }

  return connections;
}

FlightConnection FlightConnection::FindConnectionById(const std::string &id) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("identifier", id));

  bsoncxx::document::view filter_view = filter_builder.view();

  mongocxx::cursor cursor = _collection_.find(filter_view);
  for (auto &&doc : cursor) {
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
  return FlightConnection{"", "", "", "", "", 0, 0};
}

std::vector<FlightConnection> FlightConnection::FindConnectionsByDeparture(const std::string &departure_city) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("departureCity", departure_city));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  std::vector<FlightConnection> connections;

  for (auto &&doc : cursor) {
    bsoncxx::document::view view = doc;
    auto flightId = (std::string) view["identifier"].get_string().value;
    auto depCity = (std::string) view["departureCity"].get_string().value;
    auto destCity = (std::string) view["destinationCity"].get_string().value;
    auto depTime = (std::string) view["departureTime"].get_string().value;
    auto arrTime = (std::string) view["arrivalTime"].get_string().value;
    auto avSeats = view["availableSeats"].get_int32().value;
    double flightPrice = view["price"].get_int32().value;
    connections.emplace_back(flightId, depCity, destCity, depTime, arrTime, avSeats, flightPrice);
  }

  return connections;
}

std::vector<FlightConnection> FlightConnection::FindConnectionsByDestination(const std::string &destination_city) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("destinationCity", destination_city));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  std::vector<FlightConnection> connections;

  for (auto &&doc : cursor) {
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

std::vector<int> FlightConnection::GetSeatsTaken(const std::string &flight_identifier) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("identifier", flight_identifier));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  std::vector<int> seatsTaken;

  for (auto &&doc : cursor) {
    bsoncxx::document::view view = doc;
    auto seats = view["seatsTaken"].get_array().value;
    for (auto &&seat : seats) {
      seatsTaken.push_back(seat.get_int32().value);
    }
  }

  return seatsTaken;
}

void FlightConnection::UpdateSeatsTaken(const std::string &flight_identifier, const std::vector<int> &seats_taken) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("identifier", flight_identifier));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  std::vector<int> oldSeatsTaken;
  int avSeats{};
  for (auto &&doc : cursor) {
    bsoncxx::document::view view = doc;
    auto seats = view["seatsTaken"].get_array().value;
    avSeats = view["availableSeats"].get_int32().value;
    for (auto &&seat : seats) {
      oldSeatsTaken.push_back(seat.get_int32().value);
    }
  }

  for (auto &&seat : seats_taken) {
    if (std::find(oldSeatsTaken.begin(), oldSeatsTaken.end(), seat) != oldSeatsTaken.end()) {
      PrintErrorMessage("Miejsce " + std::to_string(seat) + " jest już zajęte.", "Wybierz inne miejsce.");
      return;
    }
    oldSeatsTaken.push_back(seat);
  }

  bsoncxx::builder::basic::array array_builder{};
  for (const auto &seat : oldSeatsTaken) {
    array_builder.append(seat);
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("seatsTaken", array_builder),
          bsoncxx::builder::basic::kvp("availableSeats", avSeats - (int) seats_taken.size()))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view, update_view);
}