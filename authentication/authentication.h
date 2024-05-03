/**
 * @file authentication.h
 * @brief This file contains the declaration of the Authentication class.
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
 * @brief This class handles user authentication.
 */
class Authentication {
 private:
  mongocxx::client _client_; ///< The MongoDB client.
  mongocxx::database _db_; ///< The MongoDB database.
  mongocxx::collection _collection_; ///< The MongoDB collection.

 public:
  /**
   * @brief Constructs a new Authentication object.
   * @param uri_str The URI string.
   * @param db_name The database name.
   * @param collection_name The collection name.
   */
  Authentication(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);

  /**
   * @brief Hashes a password.
   * @param password The password to hash.
   * @return The hashed password.
   */
  static std::string HashPassword(const std::string &password);

  /**
   * @brief Registers a new user.
   * @param username The username of the user.
   * @param email The email of the user.
   * @param password The password of the user.
   * @return A boolean indicating if the registration was successful.
   */
  bool RegisterUser(const std::string &username, const std::string &email, const std::string &password);

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @param promise A promise for the result of the authentication.
   * @param user The User object.
   */
  void AuthenticateUser(const std::string &username,
                        const std::string &password,
                        std::promise<bool> &&promise,
                        User &user);
};

#endif  // AUTHENTICATION_H