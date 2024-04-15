#ifndef USER_H
#define USER_H

#include <string>
#include "mongocxx/client.hpp"
#include "../flights/FlightConnection.h"

class User {
private:
    mongocxx::client& _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
    std::string password;
public:
    explicit User(mongocxx::client& client) :
    _client(client), _db(client["projekt"]), _collection(_db["users"]),
    username("gosc"), email("brak"), discount(0.0), discountType("brak"), premiumCard("brak"),
    paymentMethod("blik"), profession("brak"), registrationDate("brak"),
    moneySpent(0), moneySaved(0), ticketBought(0), userFlights(std::vector<bsoncxx::document::value>{}) {}
    User(std::string username, std::string email, double discount,
         std::string discountType, std::string premiumCard,
         std::string paymentMethod, mongocxx::client &client,
         std::string  profession, std::string registrationDate,
         double moneySpent, double moneySaved,
         int ticketBought, std::vector<bsoncxx::document::value> userFlights);

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

    // Funkcje użytkownika (metody)
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
    std::string recognizeDiscount();
    void addTicketToUser(const std::vector<int>& seats, const FlightConnection& flightConnection);
    void updateMoneySaved(double normalPrice, double discountPrice);

};

#endif // USER_H
