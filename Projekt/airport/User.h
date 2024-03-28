#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string email;
    double saldo;

public:
    User() : username("gosc"), email("brak"), saldo(0) {}
    User(const std::string& username, const std::string& email, double saldo = 0);
    std::string getUsername() const;
    std::string getEmail() const;
    static User getUser() ;
    double getSaldo() const;
    void setSaldo(double newSaldo);
};

#endif // USER_H
