#include "User.h"

#include <utility>

User::User(std::string  username, std::string  email, double saldo)
        : username(std::move(username)), email(std::move(email)), saldo(saldo) {}

std::string User::getUsername() const { return username; }

std::string User::getEmail() const { return email; }

double User::getSaldo() const { return saldo; }

void User::setSaldo(double newSaldo) { saldo = newSaldo; }

User User::getUser() {
    return {};
}