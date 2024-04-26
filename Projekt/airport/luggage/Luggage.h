//
// Created by szymo on 26.04.2024.
//

#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H


#include <vector>
#include <iostream>
#include "item/Item.h"

class Luggage {
    std::vector<Item> items;
    double maxWeight = 20.0;
    double totalWeight = 0.0;
    const double maxAllowedWeight = 32.0;
    const double overweightFeePerKg = 2.0;
    const double euroToPln = 4.32; // tworzyłem to na obecnym kursie

public:
    void addItem(const Item& item) {
        if (totalWeight + item.getWeight() > maxAllowedWeight) {
            std::cout<< "Dodanie tego przedmiotu przekroczy maksymalną wagę." << std::endl;
        }
        items.push_back(item);
        totalWeight += item.getWeight();
    }

    [[nodiscard]] double calculateOverweightFee() const {
        if (totalWeight <= maxWeight) {
            return 0.0;
        }
        double overweight = totalWeight - maxWeight;
        double feeInEuros = overweight * overweightFeePerKg;
        return feeInEuros * euroToPln;
    }
};


#endif //AIRPORT_LUGGAGE_H
