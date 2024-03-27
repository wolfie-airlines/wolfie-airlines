#include <iostream>
#include <chrono>
#include <thread>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

class UserAuthentication {
private:
    mongocxx::instance instance{};
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db;
    mongocxx::collection users;

public:
    UserAuthentication(const std::string& dbname, const std::string& collectionName) : db(client[dbname]), users(db[collectionName]) {}

    bool registerUser(const std::string& username, const std::string& password) {
        bsoncxx::document::value doc = bsoncxx::builder::stream::document{}
                << "username" << username
                << "password" << password
                << bsoncxx::builder::stream::finalize;

        try {
            users.insert_one(std::move(doc));
            std::cout << "Użytkownik zarejestrowany pomyślnie." << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Błąd podczas rejestracji użytkownika: " << e.what() << std::endl;
            return false;
        }
    }

    bool authenticate(const std::string& username, const std::string& password) {
        bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = users.find_one(
                bsoncxx::builder::stream::document{} << "username" << username << bsoncxx::builder::stream::finalize
        );

        if (maybe_result) {
            bsoncxx::document::view result = maybe_result->view();
            std::string storedPassword = result["password"].get_utf8().value.to_string();

            if (storedPassword == password) {
                std::cout << "Logowanie udane." << std::endl;
                return true;
            } else {
                std::cout << "Nieprawidłowe hasło." << std::endl;
                return false;
            }
        } else {
            std::cout << "Użytkownik o podanej nazwie nie istnieje." << std::endl;
            return false;
        }
    }
};