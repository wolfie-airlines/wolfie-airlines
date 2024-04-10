#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H

#include <string>
#include <utility>
#include <ostream>

namespace library {
    class Person {
        std::string name;
        std::string surname;

    public:
        Person(std::string  name, std::string  surname) : name(std::move(name)), surname(std::move(surname)) {}

        std::string ToString() const noexcept {
            return name + " " + surname;
        }
    };

    std::ostream& operator<<(std::ostream& out, const library::Person& author) {
        return out << author.ToString();
    }
}

#endif //LAB3_PERSON_H
