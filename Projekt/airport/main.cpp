#include <cstdlib>
#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

int main(int argc, char* argv[]) {
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;

    mongocxx::instance inst;

    try {
        const auto uri_str = (argc >= 2) ? argv[1] : "mongodb+srv://wolfiksw:PrincePolo1@testcluster.taymr.mongodb.net/projekt";
        auto uri = mongocxx::uri{uri_str};

        mongocxx::client client{uri};

        // Select database "projekt" and collection "projekt".
        auto db = client["projekt"];
        auto collection = db["projekt"];

        // Insert document with "ping" field.
        auto result = collection.insert_one(make_document(kvp("ping", 1)));

        if (result) {
            std::cout << "Document inserted successfully." << std::endl;
        } else {
            std::cout << "Failed to insert document." << std::endl;
            return EXIT_FAILURE;
        }

        // Run ping operation on the collection.
        auto ping_result = db.run_command(make_document(kvp("ping", 1)));

        std::cout << bsoncxx::to_json(ping_result) << std::endl;

        return EXIT_SUCCESS;
    } catch (const std::exception& ex) {
        std::cout << "Operation failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
