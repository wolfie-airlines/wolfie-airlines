/**
 * @file luggage.h
 * @brief This file contains the declaration of the Luggage class.
 */

#ifndef AIRPORT_LUGGAGE_H
#define AIRPORT_LUGGAGE_H

#include <vector>
#include <iostream>
#include "item/item.h"

class User;

/**
 * @class Luggage
 * @brief This class represents a luggage in the airport system.
 */
class Luggage {
  std::vector<Item> items_; ///< The items in the luggage.
  double total_weight_ = 0.0; ///< The total weight of the luggage.

 public:
  /**
   * @brief Constructs a new Luggage object.
   * @param items The items in the luggage.
   * @param total_weight The total weight of the luggage.
   */
  Luggage(
      const std::vector<Item> &items,
      double total_weight
  ) : items_(items), total_weight_(total_weight) {}

  /**
   * @brief Processes the items and gets the weight.
   * @return The weight of the items.
   */
  double ProcessItemsAndGetWeight();

  /**
   * @brief Confirms the items in the luggage.
   * @param user The user confirming the items.
   * @return A tuple containing a boolean indicating if the confirmation was successful and a string message.
   */
  std::tuple<bool, std::string> ConfirmItems(User &user);

  const double overweight_fee_per_kg_ = 2.0; ///< The overweight fee per kg.
  const double euro_to_pln_ = 4.32; ///< The conversion rate from euro to pln.
  const double max_allowed_weight_ = 32.0; ///< The maximum allowed weight.
  double max_weight_ = 20.0; ///< The maximum weight.

  /**
   * @brief Calculates the overweight fee.
   * @param weight The weight of the luggage.
   * @return The overweight fee.
   */
  double CalculateOverweightFee(double weight) const;
};

#endif //AIRPORT_LUGGAGE_H