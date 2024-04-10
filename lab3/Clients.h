#ifndef LAB3_CLIENTS_H
#define LAB3_CLIENTS_H

#include <vector>
#include "Client.h"

namespace library {
    class Clients {
        std::vector<Client> clients;
    public:
        explicit Clients(const std::vector<Client>& clients) : clients(clients) {}

        void AddClient(const Client& client) {
            clients.push_back(client);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::string result;
            for (const auto& client : clients) {
                result += client.ToString() + "\n";
            }
            return result;
        }
    };
}

#endif //LAB3_CLIENTS_H
