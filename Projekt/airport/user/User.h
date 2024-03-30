#ifndef USER_H
#define USER_H

#include <string>
#include "mongocxx/client.hpp"

class User {
private:
    std::string username;
    std::string email;
    bool isDisabled;
    std::string premiumCard;
    std::string paymentMethod;

    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _collection;

public:
    User() : username("gosc"), email("brak"), isDisabled(false), premiumCard("brak"), paymentMethod("blik") {}
    User(std::string  username, std::string  email, bool isDisabled, std::string premiumCard, std::string paymentMethod);
    std::string getUsername() const;
    std::string getEmail() const;
    static User getUser();
    bool getIsDisabled() const;
    std::string getPremiumCard() const;
    std::string getPaymentMethod() const;
    void setIsDisabled(bool isDisabled);
    void setPremiumCard(const std::string& premiumCard);
    void setPaymentMethod(const std::string& paymentMethod);
    bool setUsername(const std::string& username);
    bool setEmail(const std::string& email);
    bool setPassword(const std::string& password);
    //std::vector<Discount> getDiscounts();
};

#endif // USER_H
