#include <iostream>
#include "Book.h"

int main() {
    library::Book book(library::Authors(
            std::vector<library::Person>{library::Person("Jan Kowalski", "Kowalski")}), "Ksiazka", "Opis");
    std::cout << book << std::endl;
}