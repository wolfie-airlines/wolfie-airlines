//
// Created by szymo on 26.04.2024.
//

#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H


#include <vector>
#include <iostream>
#include "item/Item.h"
class User;

class Luggage {
    std::vector<Item> items;
    double maxWeight = 20.0;
    double totalWeight = 0.0;
    const double maxAllowedWeight = 32.0;
    const double overweightFeePerKg = 2.0;
    const double euroToPln = 4.32; // tworzyłem to na obecnym kursie

public:
    Luggage(
            const std::vector<Item> &items,
            double totalWeight
    ) : items(items), totalWeight(totalWeight) {}

    void getItemCount();

    std::tuple<bool, std::string> confirmItems(User& user);
};


#endif //AIRPORT_LUGGAGE_H
