#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <future>
#include <string>

#include "../user/user.h"
#include "mongocxx/v_noabi/mongocxx/client.hpp"
#include "mongocxx/v_noabi/mongocxx/database.hpp"
#include "mongocxx/v_noabi/mongocxx/instance.hpp"

class Authentication {
 private:
  mongocxx::client _client_;
  mongocxx::database _db_;
  mongocxx::collection _collection_;

 public:
  Authentication(const std::string &uri_str, const std::string &db_name, const std::string &collection_name);
  static std::string HashPassword(const std::string &password);
  bool RegisterUser(const std::string &username, const std::string &email, const std::string &password);
  void AuthenticateUser(const std::string &username,
                        const std::string &password,
                        std::promise<bool> &&promise,
                        User &user);
};

#endif  // AUTHENTICATION_H
