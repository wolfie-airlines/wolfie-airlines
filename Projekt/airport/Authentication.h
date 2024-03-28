#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/instance.hpp>
#include "User.h"
#include <future>

class Authentication {
private:
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;

public:
    Authentication(const std::string& uri_str, const std::string& db_name, const std::string& collection_name);

    bool registerUser(const std::string& username, const std::string& email, const std::string& password);
    void authenticateUser(const std::string& username, const std::string& password, std::promise<bool>&& promise, User& user);
};

#endif // AUTHENTICATION_H
