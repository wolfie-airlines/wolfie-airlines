#include "User.h"

User::User(const std::string& username, const std::string& email, double saldo)
        : username(username), email(email), saldo(saldo) {}

std::string User::getUsername() const { return username; }

std::string User::getEmail() const { return email; }

double User::getSaldo() const { return saldo; }

void User::setSaldo(double newSaldo) { saldo = newSaldo; }
