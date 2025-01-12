#ifndef FLIGHT_BINARY_TREE_H
#define FLIGHT_BINARY_TREE_H

#include <fstream>
#include <memory>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

#include "custom_flight.h"
#include "../../../user/user.h"

class BinaryTree {
    struct Node {
        std::shared_ptr<Flight> flight;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        explicit Node(std::shared_ptr<Flight> f) : flight(std::move(f)), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;
    mongocxx::uri uri = mongocxx::uri{"mongodb+srv://wolfiksw:PrincePolo1@testcluster.taymr.mongodb.net/projekt"};
    mongocxx::client client{uri};

    mongocxx::database db = client["projekt"];
    mongocxx::collection collection = db["flight_connections"];

    void addFlightToTree(std::unique_ptr<Node>& node, std::shared_ptr<Flight> flight) {
        if (!node) {
            node = std::make_unique<Node>(std::move(flight));
        } else if (flight->flight_id < node->flight->flight_id) {
            addFlightToTree(node->left, std::move(flight));
        } else {
            addFlightToTree(node->right, std::move(flight));
        }
    }

    [[nodiscard]] static std::shared_ptr<Flight> findFlightInTree(const std::unique_ptr<Node>& node, const std::string& id) {
        if (!node) {
            return nullptr;
        }
        if (node->flight->flight_id == id) {
            return node->flight;
        }
        if (id < node->flight->flight_id) {
            return findFlightInTree(node->left, id);
        }
        return findFlightInTree(node->right, id);
    }

    void inOrderTraversal(const std::unique_ptr<Node>& node, std::ofstream& file) const {
        if (!node) return;
        inOrderTraversal(node->left, file);
        file << node->flight->flight_id << " " << node->flight->departure_city << " " << node->flight->destination_city << " "
             << node->flight->departure_time << " " << node->flight->arrival_time << " " << node->flight->price << "\n";
        inOrderTraversal(node->right, file);
    }

    void removeFlightFromTree(std::unique_ptr<Node>& node, const std::string& id) {
        if (!node) return;
        if (id < node->flight->flight_id) {
            removeFlightFromTree(node->left, id);
        } else if (id > node->flight->flight_id) {
            removeFlightFromTree(node->right, id);
        } else {
            if (!node->left) {
                node = std::move(node->right);
            } else if (!node->right) {
                node = std::move(node->left);
            } else {
                const auto minNode = findMin(node->right);
                node->flight = minNode->flight;
                removeFlightFromTree(node->right, minNode->flight->flight_id);
            }
        }
    }

    static Node* findMin(const std::unique_ptr<Node>& node) {
        Node* current = node.get();
        while (current && current->left) {
            current = current->left.get();
        }
        return current;
    }

    void initializeTree() {
        for (mongocxx::cursor cursor = collection.find({}); auto&& doc : cursor) {
            auto flight_id = static_cast<std::string>(doc["identifier"].get_string().value);
            auto departure_city = static_cast<std::string>(doc["departureCity"].get_string().value);
            auto destination_city = static_cast<std::string>(doc["destinationCity"].get_string().value);
            auto departure_time = static_cast<std::string>(doc["departureTime"].get_string().value);
            auto arrival_time = static_cast<std::string>(doc["arrivalTime"].get_string().value);
            int available_seats = doc["availableSeats"].get_int32().value;
            int price = doc["price"].get_int32().value;

            const auto flight = std::make_shared<Flight>(flight_id, departure_city, destination_city, departure_time, arrival_time, available_seats, price);
            addFlightToTree(root, flight);
        }
    }

public:
    BinaryTree() {
        initializeTree();
    }

    void addFlight(const std::shared_ptr<Flight>& flight) {
        addFlightToTree(root, flight);

        bsoncxx::builder::basic::document flight_builder{};
        flight_builder.append(
        bsoncxx::builder::basic::kvp("identifier", flight->flight_id),
        bsoncxx::builder::basic::kvp("departureCity", flight->departure_city),
        bsoncxx::builder::basic::kvp("destinationCity", flight->destination_city),
        bsoncxx::builder::basic::kvp("departureTime", flight->departure_time),
        bsoncxx::builder::basic::kvp("arrivalTime", flight->arrival_time),
        bsoncxx::builder::basic::kvp("price", flight->price),
        bsoncxx::builder::basic::kvp("availableSeats", flight->available_seats),
        bsoncxx::builder::basic::kvp("seatsTaken", bsoncxx::builder::basic::make_array().view())
        );
        collection.insert_one(flight_builder.view());
    }

    [[nodiscard]] std::shared_ptr<Flight> findFlightById(const std::string& id) const {
        return findFlightInTree(root, id);
    }

    void removeFlight(const std::string& id) {
        removeFlightFromTree(root, id);
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("identifier", id));
        collection.delete_one(filter_builder.view());
    }

    void serialize(const std::string& filename) const {
        std::ofstream file(filename);
        inOrderTraversal(root, file);
    }
};

#endif //FLIGHT_BINARY_TREE_H
