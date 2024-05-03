#ifndef LAB3_EMPLOYEE_H
#define LAB3_EMPLOYEE_H

#include "Person.h"
#include "IBAN.h"
#include <string>

namespace library {
    class Employee : public Person {
        library::IBAN accountNumber;
    public:
        Employee(const std::string& name, const std::string& surname, const library::IBAN &accountNumber) : Person(name, surname), accountNumber(accountNumber) {}

        [[nodiscard]] std::string ToString() const noexcept {
            return Person::ToString() + " - " + accountNumber.ToString();
        }
    };
}

#endif //LAB3_EMPLOYEE_H