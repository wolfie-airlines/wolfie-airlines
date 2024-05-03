#ifndef LAB1_BOOK_H
#define LAB1_BOOK_H

#pragma once
#include <string>
#include <utility>
#include "Authors.h"

namespace library {
    class Book {
        Authors author;
        std::string title;
        std::string description;
    public:
        Book(Authors  author, std::string title, std::string description) : author(std::move(author)), title(std::move(title)), description(std::move(description)) {}

        [[nodiscard]] std::string ToString() const noexcept {
            return author.ToString() + " - " + title + (description.empty() ? "" : " - " + description);
        }
    };
};
#endif
