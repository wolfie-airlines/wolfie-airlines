#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H

#include <vector>
#include <iostream>
#include "item/item.h"

class User;

class Luggage {
  std::vector<Item> items_;
  double total_weight_ = 0.0;

 public:
  Luggage(
      const std::vector<Item> &items,
      double total_weight
  ) : items_(items), total_weight_(total_weight) {}

  double ProcessItemsAndGetWeight();

  std::tuple<bool, std::string> ConfirmItems(User &user);

  const double overweight_fee_per_kg_ = 2.0;
  const double euro_to_pln_ = 4.32;
  const double max_allowed_weight_ = 32.0;
  double max_weight_ = 20.0;

  double CalculateOverweightFee(double weight) const;
};

#endif //AIRPORT_LUGGAGE_H
