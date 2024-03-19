#ifndef LAB1_BOOK_H
#define LAB1_BOOK_H

#pragma once
#include <string>

namespace library {
    class Book {
        std::string author; // Zamienić na klasę authors zamiast stringa
        std::string title;
        std::string description;
    public:
        Book(const std::string &author, const std::string &title, const std::string &description) : author(author), title(title), description(description) {
        }

        std::string ToString() const noexcept {
            return author + " - " + title + (description.empty() ? "" : " - " + description);
        }
    };
};
#endif