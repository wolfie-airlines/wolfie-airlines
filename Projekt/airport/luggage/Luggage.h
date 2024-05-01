#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H

#include <vector>
#include <iostream>
#include "item/Item.h"
class User;

class Luggage {
  std::vector<Item> items;
  double totalWeight = 0.0;

 public:
  Luggage(
      const std::vector<Item> &items,
      double totalWeight
  ) : items(items), totalWeight(totalWeight) {}

  double processItemsAndGetWeight();

  std::tuple<bool, std::string> confirmItems(User &user);

  const double overweightFeePerKg = 2.0;
  const double euroToPln = 4.32;
  const double maxAllowedWeight = 32.0;
  double maxWeight = 20.0;

  double calculateOverweightFee(double weight) const;
};

#endif //AIRPORT_LUGGAGE_H
