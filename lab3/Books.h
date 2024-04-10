#ifndef LAB1_BOOKS_H
#define LAB1_BOOKS_H

#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include "Book.h"

namespace library {
    class Books {
        std::vector<library::Book> books;
    public:
        Books() = default;
        explicit Books(const std::vector<library::Book> &books) : books(books) {}
        [[nodiscard]] std::vector<library::Book> getAllBooks() const noexcept {
            return books;
        }
        void AddBook(const library::Book &book) {
            books.push_back(book);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::ostringstream oss;
            for (const auto &book : books) {
                oss << book.ToString() << std::endl;
            }

            if (books.empty()) {
                oss << "Ksiegarnia jest obecnie pusta :D." << std::endl;
            }
            return oss.str();
        }

        Books select(const std::function<bool(const library::Book&)> &predicate) const {
            library::Books result;
            for (const auto &book : this->books) {
                if (predicate(book)) {
                    result.AddBook(book);
                }
            }
            return result;
        }
    };
}

#endif
