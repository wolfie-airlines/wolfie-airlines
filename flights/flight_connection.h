/**
 * @file flight_connection.h
 * @brief This file contains the declaration of the FlightConnection class.
 */

#pragma once

#include <string>

#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"

/**
 * @class FlightConnection
 * @brief This class handles flight connections.
 */
class FlightConnection {
 private:
  std::string _flight_id_; ///< The flight ID.
  std::string _departureCity_; ///< The departure city.
  std::string _destinationTime_; ///< The destination time.
  std::string _arrivalTime_; ///< The arrival time.
  std::string _departureTime_; ///< The departure time.
  std::string _destinationCity_; ///< The destination city.
  int _availableSeats_{}; ///< The number of available seats.
  double _price_{}; ///< The price of the flight.

  mongocxx::client _client_; ///< The MongoDB client.
  mongocxx::database _db_; ///< The MongoDB database.
  mongocxx::collection _collection_; ///< The MongoDB collection.

 public:
  /**
   * @brief Constructs a new FlightConnection object.
   * @param uri_str The URI string.
   * @param db_name The database name.
   * @param collection_name The collection name.
   */
  FlightConnection(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);

  /**
   * @brief Constructs a new FlightConnection object.
   * @param flight_id The flight ID.
   * @param departure_city The departure city.
   * @param destination_city The destination city.
   * @param departure_time The departure time.
   * @param arrival_time The arrival time.
   * @param available_seats The number of available seats.
   * @param price The price of the flight.
   */
  FlightConnection(
      std::string flight_id,
      std::string departure_city,
      std::string destination_city,
      std::string departure_time,
      std::string arrival_time,
      int available_seats,
      double price);

  /**
   * @brief Gets the departure city.
   * @return The departure city.
   */
  [[nodiscard]] std::string GetDepartureCity() const;

  /**
   * @brief Gets the destination city.
   * @return The destination city.
   */
  [[nodiscard]] std::string GetDestinationCity() const;

  /**
   * @brief Gets the departure time.
   * @return The departure time.
   */
  [[nodiscard]] std::string GetDepartureTime() const;

  /**
   * @brief Gets the arrival time.
   * @return The arrival time.
   */
  [[nodiscard]] std::string GetArrivalTime() const;

  /**
   * @brief Gets the flight identifier.
   * @return The flight identifier.
   */
  [[nodiscard]] std::string GetIdentifier() const;

  /**
   * @brief Gets the number of available seats.
   * @return The number of available seats.
   */
  [[nodiscard]] int GetAvailableSeats() const;

  /**
   * @brief Gets the price of the flight.
   * @return The price of the flight.
   */
  [[nodiscard]] double GetPrice() const;

  /**
   * @brief Finds all flight connections.
   * @return A vector of all flight connections.
   */
  std::vector<FlightConnection> FindAllConnections();

  /**
   * @brief Finds a flight connection by departure and destination cities.
   * @param departure_city The departure city.
   * @param destination_city The destination city.
   * @return The found flight connection.
   */
  FlightConnection FindConnection(const std::string &departure_city, const std::string &destination_city);

  /**
   * @brief Finds flight connections by price range.
   * @param min_price The minimum price.
   * @param max_price The maximum price.
   * @return A vector of found flight connections.
   */
  std::vector<FlightConnection> FindConnectionByPrice(double &min_price, double &max_price);

  /**
   * @brief Finds a flight connection by ID.
   * @param id The flight ID.
   * @return The found flight connection.
   */
  FlightConnection FindConnectionById(const std::string &id);

  /**
   * @brief Finds flight connections by departure city.
   * @param departure_city The departure city.
   * @return A vector of found flight connections.
   */
  std::vector<FlightConnection> FindConnectionsByDeparture(const std::string &departure_city);

  /**
   * @brief Finds flight connections by destination city.
   * @param destination_city The destination city.
   * @return A vector of found flight connections.
   */
  std::vector<FlightConnection> FindConnectionsByDestination(const std::string &destination_city);

  /**
   * @brief Gets the seats taken for a specific flight.
   * @param flight_identifier The flight identifier.
   * @return A vector of seats taken.
   */
  std::vector<int> GetSeatsTaken(const std::string &flight_identifier);

  /**
   * @brief Updates the seats taken for a specific flight.
   * @param flight_identifier The flight identifier.
   * @param seats_taken A vector of seats taken.
   */
  void UpdateSeatsTaken(const std::string &flight_identifier, const std::vector<int> &seats_taken);
};