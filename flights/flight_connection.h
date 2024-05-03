#pragma once

#include <string>

#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"

class FlightConnection {
 private:
  std::string _flight_id_;
  std::string _departureCity_;
  std::string _destinationTime_;
  std::string _arrivalTime_;
  std::string _departureTime_;
  std::string _destinationCity_;
  int _availableSeats_{};
  double _price_{};

  mongocxx::client _client_;
  mongocxx::database _db_;
  mongocxx::collection _collection_;

 public:
  FlightConnection(const std::string &uri_str, const std::string &db_name, const std::string &collection_name)
      : _client_{mongocxx::uri{uri_str}}, _db_{_client_[db_name]}, _collection_{_db_[collection_name]} {}

  FlightConnection(
      std::string flight_id,
      std::string departure_city,
      std::string destination_city,
      std::string departure_time,
      std::string arrival_time,
      int available_seats,
      double price);

  [[nodiscard]] std::string GetDepartureCity() const;
  [[nodiscard]] std::string GetDestinationCity() const;
  [[nodiscard]] std::string GetDepartureTime() const;
  [[nodiscard]] std::string GetArrivalTime() const;
  [[nodiscard]] std::string GetIdentifier() const;
  [[nodiscard]] int GetAvailableSeats() const;
  [[nodiscard]] double GetPrice() const;
  std::vector<FlightConnection> FindAllConnections();
  FlightConnection FindConnection(const std::string &departure_city, const std::string &destination_city);
  std::vector<FlightConnection> FindConnectionByPrice(double &min_price, double &max_price);
  FlightConnection FindConnectionById(const std::string &id);
  std::vector<FlightConnection> FindConnectionsByDeparture(const std::string &departure_city);
  std::vector<FlightConnection> FindConnectionsByDestination(const std::string &destination_city);
  std::vector<int> GetSeatsTaken(const std::string &flight_identifier);
  void UpdateSeatsTaken(const std::string &flight_identifier, const std::vector<int> &seats_taken);
};
