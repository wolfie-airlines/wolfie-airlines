#include <iostream>
#include "Book.h"
#include "Books.h"
#include "Vector.h"

int main() {
    library::Book book("Mickiewicz", "Pan Tadeusz", "Epopeja narodowa Polski");
    std::cout << book.ToString() << std::endl;

    // konstruktor domyślny w zupełności wystarczy
    library::Books books;
    books.AddBook(library::Book("Mickiewicz", "Dziady", "Dramat narodowy"));
    books.AddBook(library::Book("Sienkiewicz", "Potop", "Historia Polski w czasach potopu szwedzkiego"));
    std::cout << books.ToString() << std::endl;

    library::Vector vector(5, 3.14);
    std::cout << vector.ToString() << std::endl;

    return 0;
}