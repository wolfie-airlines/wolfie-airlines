/**
 * @file authentication.h
 * @brief Ten plik zawiera deklarację klasy Authentication.
 */

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <future>
#include <string>

#include "../user/user.h"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/instance.hpp"

/**
 * @class Authentication
 * @brief Ta klasa obsługuje uwierzytelnianie użytkownika.
 */
class Authentication {
 private:
  mongocxx::client _client_; ///< Klient MongoDB.
  mongocxx::database _db_; ///< Baza danych MongoDB.
  mongocxx::collection _collection_; ///< Kolekcja MongoDB.

 public:
  /**
   * @brief Konstruuje nowy obiekt Authentication.
   * @param uri_str Ciąg URI.
   * @param db_name Nazwa bazy danych.
   * @param collection_name Nazwa kolekcji.
   */
  Authentication(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);

  /**
   * @brief Haszuje hasło.
   * @param password Hasło do zahashowania.
   * @return Zahashowane hasło.
   */
  static std::string HashPassword(const std::string &password);

  /**
   * @brief Rejestruje nowego użytkownika.
   * @param username Nazwa użytkownika.
   * @param email Email użytkownika.
   * @param password Hasło użytkownika.
   * @return Wartość logiczna wskazująca, czy rejestracja była udana.
   */
  bool RegisterUser(const std::string &username, const std::string &email, const std::string &password);

  /**
   * @brief Uwierzytelnia użytkownika.
   * @param username Nazwa użytkownika.
   * @param password Hasło użytkownika.
   * @param promise Obietnica wyniku uwierzytelnienia.
   * @param user Obiekt User.
   */
  void AuthenticateUser(const std::string &username,
                        const std::string &password,
                        std::promise<bool> &&promise,
                        User &user);
};

#endif  // AUTHENTICATION_H