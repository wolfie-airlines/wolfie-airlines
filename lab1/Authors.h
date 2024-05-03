#ifndef LAB1_AUTHORS_H
#define LAB1_AUTHORS_H

#include <string>
#include <utility>

namespace library {
    class Authors {
        std::string name;
        std::string surname;
    public:
        Authors(std::string name, std::string surname) : name(std::move(name)), surname(std::move(surname)) {
        }

        [[nodiscard]] std::string ToString() const noexcept {
            return name + " " + surname;
        }
    };
}
#endif
