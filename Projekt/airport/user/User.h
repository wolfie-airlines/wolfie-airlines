#ifndef USER_H
#define USER_H

#include <string>
#include "mongocxx/client.hpp"

class User {
private:
    mongocxx::client& _client;
    mongocxx::database _db;
    mongocxx::collection _collection;
public:
    explicit User(mongocxx::client& client) : _client(client), _db(client["projekt"]), _collection(_db["users"]),
                                     username("gosc"), email("brak"), isDisabled(false), premiumCard("brak"), paymentMethod("blik") {}
    User(std::string username, std::string email, bool isDisabled, std::string premiumCard,
         std::string password,
         std::string paymentMethod, mongocxx::client &client);

    // Obiekt użytkownika
    std::string username;
    std::string password;
    std::string email;
    bool isDisabled;
    std::string premiumCard;
    std::string paymentMethod;

    // Funkcje użytkownika
    std::string getUsername() const;
    std::string getEmail() const;
    User getUser();
    bool getIsDisabled() const;
    std::string getPremiumCard() const;
    std::string getPaymentMethod() const;
    void setIsDisabled(bool isDisabled);
    void setPremiumCard(const std::string& premiumCard);
    void setPaymentMethod(const std::string& paymentMethod);
    void changeUsername(const std::string& username);
    bool setEmail(const std::string& email);
    bool setPassword(const std::string& password);
    //std::vector<Discount> getDiscounts();

};

#endif // USER_H
