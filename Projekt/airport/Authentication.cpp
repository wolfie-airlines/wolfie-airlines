#include "Authentication.h"
#include "User.h"
#include "bsoncxx/json.hpp"

Authentication::Authentication(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
        : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

User Authentication::registerUser(const std::string& username, const std::string& email, const std::string& password) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("email", email));
    document.append(bsoncxx::builder::basic::kvp("password", password));
    document.append(bsoncxx::builder::basic::kvp("saldo", 0)); // jak rejestruje sie to saldo = 0

    auto result = _collection.insert_one(document.view());
    if (result) {
        std::cout << document.view()["email"].get_string().value;
        return User{username, email};
    } else {
        throw std::runtime_error("Wystapil blad podczas rejestracji uzytkownika.");
    }
}

User Authentication::authenticateUser(const std::string& username, const std::string& password) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("password", password));

    auto result = _collection.find_one(document.view());
    if (result) {
        bsoncxx::document::view userView = result->view();
        std::cout << bsoncxx::to_json(userView) << std::endl;

    } else {
        throw std::runtime_error("Wprowadzono niepoprawne dane badz taki uzytkownik nie istnieje.");
    }
}
