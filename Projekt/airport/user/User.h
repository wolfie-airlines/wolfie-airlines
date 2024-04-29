#ifndef USER_H
#define USER_H

#include <string>
#include "mongocxx/client.hpp"
#include "../flights/FlightConnection.h"
#include "../luggage/Luggage.h"

class User {
private:
    mongocxx::database _db;
    mongocxx::collection _collection;
    std::string password;
protected:
    mongocxx::client& _client;
public:
    explicit User(mongocxx::client& client) :
    _client(client), _db(client["projekt"]), _collection(_db["users"]),
    username("gosc"), email("brak"), discount(1.0), discountType("brak"), premiumCard("brak"),
    paymentMethod("blik"), profession("brak"), registrationDate("brak"),
    moneySpent(0), moneySaved(0), ticketBought(0), userFlights(std::vector<bsoncxx::document::value>{}), isAdmin(false) {}
    User(std::string username, std::string email, double discount,
         std::string discountType, std::string premiumCard,
         std::string paymentMethod, mongocxx::client &client,
         std::string  profession, std::string registrationDate,
         double moneySpent, double moneySaved,
         int ticketBought, std::vector<bsoncxx::document::value> userFlights, bool isAdmin);

    // Obiekt użytkownika (dane)
    std::string username;
    std::string profession;
    std::string email;
    std::string discountType;
    double discount;
    std::string premiumCard;
    std::string paymentMethod;
    std::string registrationDate;
    double moneySpent;
    double moneySaved;
    int ticketBought;
    std::vector<bsoncxx::document::value> userFlights;
    bool isAdmin;

    // Funkcje użytkownika (metody)
    void reset();
    mongocxx::collection& getCollection();
    mongocxx::collection getSpecificCollection(const std::string &collectionName);
    std::string getPassword();
    void setPassword(const std::string& password);
    void setPremiumCard(User& user, const std::string& card);
    void setBlik(const std::string& paymentMethod);
    void setVisa(const std::string& cNumber, const std::string& cCVV);
    void changeUsername(const std::string& username);
    void changeEmail(const std::string& email);
    void changePassword(const std::string& password);
    void setDiscount(double discount, const std::string& discountType);
    [[nodiscard]] double getDiscount() const;
    [[nodiscard]] std::string recognizeDiscount() const;
    void addTicketToUser(const std::vector<int>& seats, const FlightConnection& flightConnection);
    void updateMoneySaved(double normalPrice, double discountPrice);
    void loginAsAdmin();
    [[nodiscard]] bool checkIfAdmin() const;
    void setIsAdmin(bool isAdministrator) { User::isAdmin = isAdministrator; }
};

#endif // USER_H
