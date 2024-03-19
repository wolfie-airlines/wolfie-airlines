#ifndef LAB1_VECTOR_H
#define LAB1_VECTOR_H

#include <string>
#include <sstream>

namespace library {
    class Vector {
        size_t size;
        double* data;

    public:
        explicit Vector(const size_t size, const double value = 0.0) : size(size), data(new double[size]) {
            for (size_t i = 0; i < size; i++) {
                data[i] = value;
            }
        }

        ~Vector() noexcept {
            delete[] data;
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::ostringstream oss;
            for (size_t i = 0; i < size; i++) {
                oss << data[i] << std::endl;
            }
            return oss.str();
        }
    };
}

#endif
