#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <future>
#include <string>

#include "../user/User.h"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/instance.hpp"

class Authentication {
 private:
  mongocxx::client _client;
  mongocxx::database _db;
  mongocxx::collection _collection;

 public:
  Authentication(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);
  static std::string hashPassword(const std::string &password);
  bool registerUser(const std::string &username, const std::string &email, const std::string &password);
  void authenticateUser(const std::string &username,
                        const std::string &password,
                        std::promise<bool> &&promise,
                        User &user);
};

#endif  // AUTHENTICATION_H
