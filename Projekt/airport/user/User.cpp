#include "User.h"

#include <utility>

User::User(std::string  username, std::string  email, bool isDisabled, std::string premiumCard, std::string paymentMethod)
        : username(std::move(username)), email(std::move(email)), isDisabled(isDisabled), premiumCard(std::move(premiumCard)), paymentMethod(std::move(paymentMethod))
{}

std::string User::getUsername() const { return username; }

std::string User::getEmail() const { return email; }

User User::getUser() {
    return {};
}

bool User::getIsDisabled() const {
    return isDisabled;
}

std::string User::getPremiumCard() const {
    return premiumCard;
}

std::string User::getPaymentMethod() const {
    return paymentMethod;
}

void User::setIsDisabled(bool isDis) {
    isDisabled = isDis;
}

void User::setPremiumCard(const std::string &card) {
    premiumCard = card;
}

void User::setPaymentMethod(const std::string &payment) {
    paymentMethod = payment;
}
