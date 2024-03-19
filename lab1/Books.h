
#ifndef LAB1_BOOKS_H
#define LAB1_BOOKS_H

#include <string>
#include <vector>
#include <sstream>
#include "Book.h"

namespace library {
    class Books {
        std::vector<library::Book> books;
    public:
        void AddBook(const library::Book &book) {
            books.push_back(book);
        }

        std::string ToString() const noexcept {
            std::ostringstream oss;
            for (const auto &book : books) {
                oss << book.ToString() << std::endl;
            }
            return oss.str();
        }
    };
}

#endif
