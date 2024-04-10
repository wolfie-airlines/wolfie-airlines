#ifndef LAB3_IBAN_H
#define LAB3_IBAN_H

#include <string>

namespace library {
    class IBAN {
    public:
        IBAN(const std::string& iban) : iban(iban) {}
        [[nodiscard]] std::string ToString() const noexcept {
            return iban;
        }

        const std::string &iban;
    };
}

#endif //LAB3_IBAN_H
