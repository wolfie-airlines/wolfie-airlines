#include <cstdlib>
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include "EnvParser.h"
#include "Authentication.h"

int main(int argc, char* argv[]) {
    mongocxx::instance inst;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    EnvParser parser;
    parser.parseEnvFile();

    try {
        const auto uri_str = (argc >= 2) ? argv[1] : parser.getValue("DATABASE_URL");
        auto uri = mongocxx::uri{uri_str};

        mongocxx::client client{uri};

        Authentication auth{uri_str, "projekt", "users"};

        auto db = client["projekt"];
        auto collection = db["connection_test"];

        // testowy dokument dla pingu do kolekcji
        auto result = collection.insert_one(make_document(kvp("ping", 1)));

        if (result) {
            std::cout << "Spingowano baze danych." << std::endl;
        } else {
            std::cout << "Nie udalo sie..." << std::endl;
            return EXIT_FAILURE;
        }

        // testowy wysyłany ping do bazy danych
        auto ping_result = db.run_command(make_document(kvp("ping", 1)));

        std::cout << bsoncxx::to_json(ping_result) << std::endl;

        std::cout << "Zaloguj się lub zarejestruj, aby kontynuować." << std::endl;
        std::cout << "1. Zarejestruj" << std::endl;
        std::cout << "2. Zaloguj" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string username, email, password;
            std::cout << "Podaj nazwę użytkownika: ";
            std::cin >> username;
            std::cout << "Podaj email: ";
            std::cin >> email;
            std::cout << "Podaj hasło: ";
            std::cin >> password;
            auth.registerUser(username, email, password);
        } else if (choice == 2) {
            std::string username, password;
            std::cout << "Podaj nazwę użytkownika: ";
            std::cin >> username;
            std::cout << "Podaj hasło: ";
            std::cin >> password;
            auth.authenticateUser(username, password);
        } else {
            std::cout << "Nieprawidłowy wybór." << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cout << "Blad operacji: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
