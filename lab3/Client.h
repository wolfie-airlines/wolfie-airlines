#ifndef LAB3_CLIENT_H
#define LAB3_CLIENT_H

#include "Person.h"
#include <string>

namespace library {
    class Client : public Person {
    public:
        Client(const std::string& name, const std::string& surname, double money) : Person(name, surname), money(money) {}
        double money;
    };
}

#endif //LAB3_CLIENT_H
