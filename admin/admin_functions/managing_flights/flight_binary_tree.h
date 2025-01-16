#ifndef FLIGHT_BINARY_TREE_H
#define FLIGHT_BINARY_TREE_H

#include <fstream>
#include <memory>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

#include "custom_flight.h"
#include "../../../user/user.h"

template<typename T>
class BinaryTree {
    struct Node {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        explicit Node(std::shared_ptr<T> d) : data(std::move(d)), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;


    User& admin;

    void addDataToTree(std::unique_ptr<Node>& node, std::shared_ptr<T> data) {
        if (!node) {
            node = std::make_unique<Node>(std::move(data));
        } else if (data->flight_id < node->data->flight_id) {
            addDataToTree(node->left, std::move(data));
        } else {
            addDataToTree(node->right, std::move(data));
        }
    }

    [[nodiscard]] static std::shared_ptr<T> findDataInTree(const std::unique_ptr<Node>& node, const std::string& id) {
        if (!node) {
            return nullptr;
        }
        if (node->data->flight_id == id) {
            return node->data;
        }
        if (id < node->data->flight_id) {
            return findDataInTree(node->left, id);
        }
        return findDataInTree(node->right, id);
    }

    void inOrderTraversal(const std::unique_ptr<Node>& node, std::ofstream& file) const {
        if (!node) return;
        inOrderTraversal(node->left, file);
        file << node->data->flight_id << " " << node->data->departure_city << " " << node->data->destination_city << " "
             << node->data->departure_time << " " << node->data->arrival_time << " " << node->data->price << "\n";
        inOrderTraversal(node->right, file);
    }

    void removeDataFromTree(std::unique_ptr<Node>& node, const std::string& id) {
        if (!node) return;
        if (id < node->data->flight_id) {
            removeDataFromTree(node->left, id);
        } else if (id > node->data->flight_id) {
            removeDataFromTree(node->right, id);
        } else {
            if (!node->left) {
                node = std::move(node->right);
            } else if (!node->right) {
                node = std::move(node->left);
            } else {
                const auto minNode = findMin(node->right);
                node->data = minNode->data;
                removeDataFromTree(node->right, minNode->data->flight_id);
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
        for (mongocxx::cursor cursor = admin.GetSpecificCollection("flight_connections").find({}); auto&& doc : cursor) {
            auto flight_id = static_cast<std::string>(doc["identifier"].get_string().value);
            auto departure_city = static_cast<std::string>(doc["departureCity"].get_string().value);
            auto destination_city = static_cast<std::string>(doc["destinationCity"].get_string().value);
            auto departure_time = static_cast<std::string>(doc["departureTime"].get_string().value);
            auto arrival_time = static_cast<std::string>(doc["arrivalTime"].get_string().value);
            int available_seats = doc["availableSeats"].get_int32().value;
            int price = doc["price"].get_int32().value;

            const auto data = std::make_shared<T>(flight_id, departure_city, destination_city, departure_time, arrival_time, available_seats, price);
            addDataToTree(root, data);
        }
    }

public:
    explicit BinaryTree(User& user) : root(nullptr), admin(user) {
        initializeTree();
    }

    void addData(const std::shared_ptr<T>& data) {
        addDataToTree(root, data);

        bsoncxx::builder::basic::document data_builder{};
        data_builder.append(
        bsoncxx::builder::basic::kvp("identifier", data->flight_id),
        bsoncxx::builder::basic::kvp("departureCity", data->departure_city),
        bsoncxx::builder::basic::kvp("destinationCity", data->destination_city),
        bsoncxx::builder::basic::kvp("departureTime", data->departure_time),
        bsoncxx::builder::basic::kvp("arrivalTime", data->arrival_time),
        bsoncxx::builder::basic::kvp("price", data->price),
        bsoncxx::builder::basic::kvp("availableSeats", data->available_seats),
        bsoncxx::builder::basic::kvp("seatsTaken", bsoncxx::builder::basic::make_array().view())
        );

        admin.GetSpecificCollection("flight_connections").insert_one(data_builder.view());
    }

    [[nodiscard]] std::shared_ptr<T> findDataById(const std::string& id) const {
        return findDataInTree(root, id);
    }

    void removeData(const std::string& id) {
        removeDataFromTree(root, id);
        bsoncxx::builder::basic::document filter_builder{};
        filter_builder.append(bsoncxx::builder::basic::kvp("identifier", id));
        admin.GetSpecificCollection("flight_connections").delete_one(filter_builder.view());
    }

    void serialize(const std::string& filename) const {
        std::ofstream file(filename);
        inOrderTraversal(root, file);
    }

    class Iterator {
        struct StackNode {
            Node* node;
            StackNode* next;
        };

        StackNode* stackTop;

        void push(Node* node) {
            auto* newNode = new StackNode{node, stackTop};
            stackTop = newNode;
        }

        Node* pop() {
            if (!stackTop) return nullptr;
            StackNode* topNode = stackTop;
            stackTop = stackTop->next;
            Node* node = topNode->node;
            delete topNode;
            return node;
        }

        void pushLeft(Node* node) {
            while (node) {
                push(node);
                node = node->left.get();
            }
        }

    public:
        explicit Iterator(Node* root) : stackTop(nullptr) {
            pushLeft(root);
        }

        ~Iterator() {
            while (stackTop) {
                pop();
            }
        }

        [[nodiscard]] bool hasNext() const {
            return stackTop != nullptr;
        }

        std::shared_ptr<T> next() {
            Node* node = pop();
            pushLeft(node->right.get());
            return node->data;
        }
    };

    Iterator begin() {
        return Iterator(root.get());
    }
};

#endif //FLIGHT_BINARY_TREE_H