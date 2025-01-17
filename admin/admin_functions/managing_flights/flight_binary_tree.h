#ifndef FLIGHT_BINARY_TREE_H
#define FLIGHT_BINARY_TREE_H

#include <fstream>
#include <memory>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

#include "custom_flight.h"
#include "custom_stack.h"
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

    // ReSharper disable once CppDFAUnreachableFunctionCall
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
        for (auto it = begin(); it != end(); ++it) {
            auto data = *it;
            file << data->flight_id << " " << data->departure_city << " " << data->destination_city << " "
                 << data->departure_time << " " << data->arrival_time << " " << data->price << "\n";
        }
    }

    class Iterator {
        Node* current;
        Stack<Node*> stack;

        void pushLeft(Node* node) {
            while (node) {
                stack.push(node);
                node = node->left.get();
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* root) : current(nullptr) {
            pushLeft(root);
            if (!stack.isEmpty()) {
                current = stack.pop();
            }
        }

        Iterator& operator++() {
            if (current) {
                pushLeft(current->right.get());
                if (!stack.isEmpty()) {
                    current = stack.pop();
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        std::shared_ptr<T> operator*() const {
            return current->data;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() const {
        return Iterator(root.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif //FLIGHT_BINARY_TREE_H