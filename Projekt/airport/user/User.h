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
                                     username("gosc"), email("brak"), isDisabled(false), premiumCard("brak"), paymentMethod("blik"), profession("brak") {}
    User(std::string username, std::string email, bool isDisabled, std::string premiumCard,
         std::string password,
         std::string paymentMethod, mongocxx::client &client, std::string  profession);

    // Obiekt użytkownika (dane)
    std::string username;
    std::string profession;
    std::string password;
    std::string email;
    bool isDisabled;
    std::string premiumCard;
    std::string paymentMethod;

    // Funkcje użytkownika (metody)
//TODO: void setIsDisabled(bool isDisabled);
    void setPremiumCard(const std::string& premiumCard);
    void setPaymentMethod(const std::string& paymentMethod);
    void handleVisa(const std::string& cNumber, const std::string& cCVV);
    void changeUsername(const std::string& username);
    void changeEmail(const std::string& email);
    void changePassword(const std::string& password);
    //std::vector<Discount> getDiscounts();

};

#endif // USER_H
