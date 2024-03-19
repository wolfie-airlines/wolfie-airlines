#ifndef LAB1_AUTHORS_H
#define LAB1_AUTHORS_H

#include <string>

namespace library {
    class Authors {
        std::string name;
        std::string surname;
    public:
        Authors(const std::string &name, const std::string &surname) : name(name), surname(surname) {
        }

        std::string ToString() const noexcept {
            return name + " " + surname;
        }
    };
}
#endif
