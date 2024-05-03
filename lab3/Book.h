#ifndef LAB1_BOOK_H
#define LAB1_BOOK_H

#pragma once
#include <string>
#include <utility>
#include "Authors.h"

namespace library {
    class Book {
        Authors authors;
        std::string title;
        std::string description;
    public:
        Book(Authors   authors, std::string  title, std::string description) : authors(std::move(authors)), title(std::move(title)), description(std::move(description)) {}

        [[nodiscard]] std::string ToString() const noexcept {
            return authors.ToString() + " - " + title + (description.empty() ? "" : " - " + description);
        }
    };

    std::ostream& operator<<(std::ostream& out, const library::Book book) {
        return out << book.ToString();
    }
};
#endif
