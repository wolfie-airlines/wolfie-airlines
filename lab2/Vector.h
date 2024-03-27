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

        Vector& operator=(const library::Vector& v) {
            if (this == &v) {
                return *this;
            }
            delete[] data;
            size = v.size;
            data = new double[size];
            memcpy(data, v.data, sizeof(*data) * size);
            return *this;
        }

        Vector& operator=(library::Vector&& v) noexcept {
            if (this == &v) {
                return *this;
            }
            delete[] data;
            size = v.size;
            data = v.data;
            v.size = 0;
            v.data = nullptr;
            return *this;
        }

        bool operator+=(const library::Vector& v)  {
            if (size != v.size) {
                throw std::exception();
            }
            for (size_t i = 0; i < size; i++) {
                data[i] += v.data[i];
            }
            return true;
        }

        library::Vector operator+(const double v) const {
            for (size_t i = 0; i < size; i++) {
                data[i] += v;
            }
            return *this;
        }

        bool operator==(const library::Vector& v) const noexcept {
            if (size != v.size) {
                return false;
            }
            for (size_t i = 0; i < size; i++) {
                if (data[i] != v.data[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const library::Vector& v) const noexcept {
            return !(*this == v);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::ostringstream oss;
            for (size_t i = 0; i < size; i++) {
                oss << data[i] << std::endl;
            }
            return oss.str();
        }

        double operator[](const size_t i) const {
            if(i >= size) throw std::exception();
            return data[i];
        }

        double& operator[](const size_t i) {
            return data[i];
        }

        [[nodiscard]] size_t Size() const noexcept {
            return size;
        }

        library::Vector operator++() noexcept {
            for (size_t i = 0; i < size; i++) {
                ++data[i];
            }
            return *this;
        }

        library::Vector operator++(int) noexcept {
            library::Vector v(*this);
            for (size_t i = 0; i < size; i++) {
                ++data[i];
            }
            return v;
        }
    };

    library::Vector operator+(library::Vector l, const library::Vector& vector) {
        l += vector;
        return l;
    }
}

#endif
