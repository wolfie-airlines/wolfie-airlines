#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string email;
    bool isDisabled;
    std::string premiumCard;
    std::string paymentMethod;

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
};

#endif // USER_H
