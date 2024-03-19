#ifndef LAB1_BOOK_H
#define LAB1_BOOK_H

#pragma once
#include <string>
#include "Authors.h"

namespace library {
    class Book {
        Authors author;
        std::string title;
        std::string description;
    public:
        Book(const Authors& author, const std::string &title, const std::string &description) : author(author), title(title), description(description) {}

        std::string ToString() const noexcept {
            return author.ToString() + " - " + title + (description.empty() ? "" : " - " + description);
        }
    };
};
#endif
