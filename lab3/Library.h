#ifndef LAB3_LIBRARY_H
#define LAB3_LIBRARY_H

#include <utility>
#include "Employees.h"
#include "Books.h"
#include "Client.h"
#include "Clients.h"

namespace library {
    class Library {
        Books books;
        Employees employees;
        Clients clients;
    public:
        Library(Books books, Employees employees, Clients clients)
                : books(std::move(books)), employees(std::move(employees)), clients(std::move(clients)) {}

        void AddBook(const Book &book) {
            books.AddBook(book);
        }

        void AddEmployee(const Employee &employee) {
            employees.AddEmployee(employee);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            return books.ToString() + employees.ToString();
        }

        Books findBooks(const std::function<bool(const Book&)> &predicate) const {
            return books.select(predicate);
        }
    };
}

#endif //LAB3_LIBRARY_H
