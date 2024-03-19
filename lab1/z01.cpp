#include <iostream>
#include "Authors.h"
#include "Books.h"
#include "Vector.h"

int main() {
    library::Authors author1("Adam", "Mickiewicz");
    library::Authors author2("Henryk", "Sienkiewicz");

    library::Books books;
    books.AddBook(library::Book(author1, "Pan Tadeusz", "Epopeja narodowa Polski"));
    books.AddBook(library::Book(author1, "Dziady", "Dramat narodowy"));
    books.AddBook(library::Book(author2, "Potop", "Historia Polski w czasach potopu szwedzkiego"));
    std::cout << books.ToString() << std::endl;

    library::Vector vector(5, 3.14);
    std::cout << vector.ToString() << std::endl;

    return 0;
}
