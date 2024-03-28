#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string email;
    double saldo;

public:
    User(const std::string& username, const std::string& email, double saldo = 0);

    std::string getUsername() const;
    std::string getEmail() const;
    double getSaldo() const;
    void setSaldo(double newSaldo);
};

#endif // USER_H
