//
// Created by szymo on 26.04.2024.
//

#ifndef AIRPORT_ITEM_H
#define AIRPORT_ITEM_H


#include <string>
#include <vector>

class Item {
    std::string itemName;
    std::string description;
    std::vector<std::string> hints;
    bool forbidden;
    bool registeredLuggage;
    bool handLuggage;
    bool pilotAllowance;
    double maxCount;
    double weight;

public:
    Item(const std::string &itemName, const std::string &description, const std::vector<std::string> &hints, bool forbidden,
         bool registeredLuggage, bool handLuggage, bool pilotAllowance, double maxCount, double weight);

    [[nodiscard]] const std::string &getItemName() const;

    [[nodiscard]] const std::string &getDescription() const;

    [[nodiscard]] const std::vector<std::string> &getHints() const;

    [[nodiscard]] bool isForbidden() const;

    [[nodiscard]] bool isRegisteredLuggage() const;

    [[nodiscard]] bool isHandLuggage() const;

    [[nodiscard]] bool isPilotAllowance() const;

    [[nodiscard]] double getMaxCount() const;

    [[nodiscard]] double getWeight() const;

};


#endif //AIRPORT_ITEM_H
