#ifndef LAB3_EMPLOYEES_H
#define LAB3_EMPLOYEES_H

#include <vector>
#include "Employee.h"

namespace library {
    class Employees {
        std::vector<Employee> employees;
    public:
        explicit Employees(const std::vector<Employee>& employees) : employees(employees) {}

        void AddEmployee(const Employee& employee) {
            employees.push_back(employee);
        }

        [[nodiscard]] std::string ToString() const noexcept {
            std::string result;
            for (const auto& employee : employees) {
                result += employee.ToString() + "\n";
            }
            return result;
        }
    };
}

#endif //LAB3_EMPLOYEES_H
