#include <cstdlib>
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include "EnvParser.h"

int main(int argc, char* argv[]) {
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    EnvParser parser;
    parser.parseEnvFile();

    mongocxx::instance inst;

    try {
        const auto uri_str = (argc >= 2) ? argv[1] : parser.getValue("DATABASE_URL");
        auto uri = mongocxx::uri{uri_str};

        mongocxx::client client{uri};

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

        return EXIT_SUCCESS;
    } catch (const std::exception& ex) {
        std::cout << "Blad operacji: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
