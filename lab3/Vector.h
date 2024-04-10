#ifndef LAB1_VECTOR_H
#define LAB1_VECTOR_H

#include <string>
#include <sstream>
#include <cstring>
#include <functional>

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

        Vector(const size_t size, const std::function<double(const size_t)>&f) : size(size), data(new double[size]) {
            for (size_t i = 0; i < size; i++) {
                data[i] = f(i);
            }
        }

        Vector(const library::Vector& v): size(v.size), data(new double[size]) {
            memcpy(data, v.data, sizeof(*data) * size);
        }

        Vector(library::Vector&& v)  noexcept : size(v.size), data(v.data) {
            v.size = 0;
            v.data = nullptr;
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
