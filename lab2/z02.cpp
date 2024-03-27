#include <iostream>
#include "Vector.h"

int main() {
    library::Vector vector(5, 3.14);
    std::cout << vector.ToString() << std::endl;

    library::Vector v2(std::move(vector));

    std::cout << vector.ToString() << std::endl;
    std::cout << v2.ToString() << std::endl;

    library::Vector v(5, [](const size_t i) { return i * i; });
    std::cout << v.ToString() << std::endl;

    if(v == v2) {
        std::cout << "Wektory sa takie same" << std::endl;
    } else {
        std::cout << "Wektory sa rozne" << std::endl;
    }

    v += v2;
    std::cout << v.ToString() << std::endl;

    ++v;
    std::cout<< v.ToString() << std::endl;

    return 0;
}
