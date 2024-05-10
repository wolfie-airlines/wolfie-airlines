#include <bsoncxx/builder/basic/document.hpp>
#include <cstdlib>
#include <iostream>

#include "authentication/authentication.h"
#include "env/env.h"
#include "flights/flight_connection.h"
#include "functions/main_handler.h"

int main() {
    mongocxx::instance inst;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    EnvParser parser;
    parser.ParseEnvFile();

    try {
        const auto uri_str = parser.GetValue("DATABASE_URL");
        auto uri = mongocxx::uri{uri_str};

        mongocxx::client client{uri};

        Authentication auth{uri_str, "projekt", "users"};
        FlightConnection flightConnection{uri_str, "projekt", "flight_connections"};

        auto db = client["projekt"];
        auto collection = db["connection_test"];

        // testowy dokument dla pingu do kolekcji
        auto an_optional = collection.insert_one(make_document(kvp("ping", 1)));

        if (!an_optional) {
            std::cout << "Failed to connect to the database...." << std::endl;
            return EXIT_FAILURE;
        }

        User current_user{client};
        bool is_logged_in = false;
        ProcessChoice(is_logged_in, auth, current_user, flightConnection);

    } catch (const std::exception &ex) {
        std::cout << "Operation error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
