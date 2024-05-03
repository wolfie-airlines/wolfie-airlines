/**
 * @file flight_connection.h
 * @brief Ten plik zawiera deklarację klasy FlightConnection.
 */

#pragma once

#include <string>

#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/collection.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"

/**
 * @class FlightConnection
 * @brief Ta klasa obsługuje połączenia lotnicze.
 */
class FlightConnection {
 private:
  std::string _flight_id_; ///< ID lotu.
  std::string _departureCity_; ///< Miasto odlotu.
  std::string _destinationTime_; ///< Czas docelowy.
  std::string _arrivalTime_; ///< Czas przyjazdu.
  std::string _departureTime_; ///< Czas odlotu.
  std::string _destinationCity_; ///< Miasto docelowe.
  int _availableSeats_{}; ///< Liczba dostępnych miejsc.
  double _price_{}; ///< Cena lotu.

  mongocxx::client _client_; ///< Klient MongoDB.
  mongocxx::database _db_; ///< Baza danych MongoDB.
  mongocxx::collection _collection_; ///< Kolekcja MongoDB.

 public:
  /**
   * @brief Konstruuje nowy obiekt FlightConnection.
   * @param uri_str Ciąg URI.
   * @param db_name Nazwa bazy danych.
   * @param collection_name Nazwa kolekcji.
   */
  FlightConnection(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);

  /**
   * @brief Konstruuje nowy obiekt FlightConnection.
   * @param flight_id ID lotu.
   * @param departure_city Miasto odlotu.
   * @param destination_city Miasto docelowe.
   * @param departure_time Czas odlotu.
   * @param arrival_time Czas przyjazdu.
   * @param available_seats Liczba dostępnych miejsc.
   * @param price Cena lotu.
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
   * @brief Pobiera miasto odlotu.
   * @return Miasto odlotu.
   */
  [[nodiscard]] std::string GetDepartureCity() const;

  /**
   * @brief Pobiera miasto docelowe.
   * @return Miasto docelowe.
   */
  [[nodiscard]] std::string GetDestinationCity() const;

  /**
   * @brief Pobiera czas odlotu.
   * @return Czas odlotu.
   */
  [[nodiscard]] std::string GetDepartureTime() const;

  /**
   * @brief Pobiera czas przyjazdu.
   * @return Czas przyjazdu.
   */
  [[nodiscard]] std::string GetArrivalTime() const;

  /**
   * @brief Pobiera identyfikator lotu.
   * @return Identyfikator lotu.
   */
  [[nodiscard]] std::string GetIdentifier() const;

  /**
   * @brief Pobiera liczbę dostępnych miejsc.
   * @return Liczba dostępnych miejsc.
   */
  [[nodiscard]] int GetAvailableSeats() const;

  /**
   * @brief Pobiera cenę lotu.
   * @return Cena lotu.
   */
  [[nodiscard]] double GetPrice() const;

  /**
   * @brief Znajduje wszystkie połączenia lotnicze.
   * @return Wektor wszystkich połączeń lotniczych.
   */
  std::vector<FlightConnection> FindAllConnections();

  /**
   * @brief Znajduje połączenie lotnicze według miasta odlotu i docelowego.
   * @param departure_city Miasto odlotu.
   * @param destination_city Miasto docelowe.
   * @return Znalezione połączenie lotnicze.
   */
  FlightConnection FindConnection(const std::string &departure_city, const std::string &destination_city);

  /**
   * @brief Znajduje połączenia lotnicze w zakresie cenowym.
   * @param min_price Minimalna cena.
   * @param max_price Maksymalna cena.
   * @return Wektor znalezionych połączeń lotniczych.
   */
  std::vector<FlightConnection> FindConnectionByPrice(double &min_price, double &max_price);

  /**
   * @brief Znajduje połączenie lotnicze według ID.
   * @param id ID lotu.
   * @return Znalezione połączenie lotnicze.
   */
  FlightConnection FindConnectionById(const std::string &id);

  /**
   * @brief Znajduje połączenia lotnicze według miasta odlotu.
   * @param departure_city Miasto odlotu.
   * @return Wektor znalezionych połączeń lotniczych.
   */
  std::vector<FlightConnection> FindConnectionsByDeparture(const std::string &departure_city);

  /**
   * @brief Znajduje połączenia lotnicze według miasta docelowego.
   * @param destination_city Miasto docelowe.
   * @return Wektor znalezionych połączeń lotniczych.
   */
  std::vector<FlightConnection> FindConnectionsByDestination(const std::string &destination_city);

  /**
   * @brief Pobiera zajęte miejsca dla określonego lotu.
   * @param flight_identifier Identyfikator lotu.
   * @return Wektor zajętych miejsc.
   */
  std::vector<int> GetSeatsTaken(const std::string &flight_identifier);

  /**
   * @brief Aktualizuje zajęte miejsca dla określonego lotu.
   * @param flight_identifier Identyfikator lotu.
   * @param seats_taken Wektor zajętych miejsc.
   */
  void UpdateSeatsTaken(const std::string &flight_identifier, const std::vector<int> &seats_taken);
};