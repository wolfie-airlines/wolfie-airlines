#ifndef LAB1_AUTHORS_H
#define LAB1_AUTHORS_H

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include "Person.h"

namespace library {
    class Authors {
        std::vector<library::Person> authors;
    public:
        explicit Authors(const std::vector<library::Person> &authors) : authors(authors) {}
        void Add(const library::Person &author) {
            authors.push_back(author);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::ostringstream oss;
            for (const auto &author : authors) {
                oss << author.ToString() << std::endl;
            }
            if (authors.empty()) {
                oss << "Brak autorow." << std::endl;
            }
            return oss.str();
        }
    };

    std::ostream& operator<<(std::ostream& out, const library::Authors& authors) {
        return out << authors.ToString();
    }
}
#endif
