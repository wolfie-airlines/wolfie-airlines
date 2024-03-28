#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
// ^ żeby nie podkreślało mi linijek
#include "Authentication.h"
#include "User.h"
#include "bsoncxx/json.hpp"

Authentication::Authentication(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
        : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

bool Authentication::registerUser(const std::string& username, const std::string& email, const std::string& password) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("email", email));
    document.append(bsoncxx::builder::basic::kvp("password", password));
    document.append(bsoncxx::builder::basic::kvp("saldo", 0)); // jak rejestruje sie to saldo = 0

    auto result = _collection.insert_one(document.view());
    return result ? true : false;
}

bool Authentication::authenticateUser(const std::string& username, const std::string& password) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("password", password));

    auto result = _collection.find_one(document.view());
    if (result) {
        bsoncxx::document::view userView = result->view();
        std::cout << bsoncxx::to_json(userView) << std::endl;
        auto email = (std::string) userView["email"].get_string().value;
        std::cout << email << std::endl;
        auto saldo = userView["saldo"].get_double().value;
        User user{username, email, saldo};
          return true;
    } else {
        std::cerr << "Wprowadzono niepoprawne dane badz taki uzytkownik nie istnieje." << std::endl;
        return false;
    }
}

#pragma clang diagnostic pop