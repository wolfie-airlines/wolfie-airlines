/**
 * @file item.h
 * @brief This file contains the declaration of the Item class.
 */

#ifndef AIRPORT_ITEM_H
#define AIRPORT_ITEM_H

#include <string>
#include <vector>

class User;

/**
 * @class Item
 * @brief This class represents an item in the airport system.
 */
class Item {
  std::string item_name_; ///< The name of the item.
  std::string description_; ///< The description of the item.
  std::vector<std::string> hints_; ///< The hints related to the item.
  bool forbidden_; ///< Indicates whether the item is forbidden.
  bool registered_luggage_; ///< Indicates whether the item can be transported as registered luggage.
  bool hand_luggage_; ///< Indicates whether the item can be transported as hand luggage.
  bool pilot_allowance_; ///< Indicates whether the item needs pilot allowance to be transported.
  double max_count_; ///< The maximum count of the item.
  double weight_; ///< The weight of the item.
  std::string profession_; ///< The profession related to the item.
  std::string category_ = "special"; ///< The category of the item.

 public:
  /**
   * @brief Constructs a new Item object.
   * @param item_name The name of the item.
   * @param description The description of the item.
   * @param hints The hints related to the item.
   * @param forbidden Indicates whether the item is forbidden.
   * @param registered_luggage Indicates whether the item can be transported as registered luggage.
   * @param hand_luggage Indicates whether the item can be transported as hand luggage.
   * @param pilot_allowance Indicates whether the item needs pilot allowance to be transported.
   * @param max_count The maximum count of the item.
   * @param weight The weight of the item.
   * @param profession The profession related to the item.
   * @param category The category of the item.
   */
  Item(const std::string &item_name,
       const std::string &description,
       const std::vector<std::string> &hints,
       bool forbidden,
       bool registered_luggage,
       bool hand_luggage,
       bool pilot_allowance,
       double max_count,
       double weight,
       std::string &profession,
       std::string &category);

  /**
   * @brief Constructs a new Item object.
   * @param item_name The name of the item.
   * @param description The description of the item.
   * @param hints The hints related to the item.
   * @param forbidden Indicates whether the item is forbidden.
   * @param registered_luggage Indicates whether the item can be transported as registered luggage.
   * @param hand_luggage Indicates whether the item can be transported as hand luggage.
   * @param pilot_allowance Indicates whether the item needs pilot allowance to be transported.
   * @param max_count The maximum count of the item.
   * @param weight The weight of the item.
   * @param category The category of the item.
   */
  Item(const std::string &item_name,
       const std::string &description,
       const std::vector<std::string> &hints,
       bool forbidden,
       bool registered_luggage,
       bool hand_luggage,
       bool pilot_allowance,
       double max_count,
       double weight,
       std::string &category);

  /**
   * @brief Gets the name of the item.
   * @return The name of the item.
   */
  [[nodiscard]] const std::string &GetItemName() const;

  /**
   * @brief Gets the description of the item.
   * @return The description of the item.
   */
  [[nodiscard]] const std::string &GetDescription() const;

  /**
   * @brief Gets the profession related to the item.
   * @return The profession related to the item.
   */
  [[nodiscard]] const std::string &GetProfession() const;

  /**
   * @brief Gets the hints related to the item.
   * @return The hints related to the item.
   */
  [[nodiscard]] const std::vector<std::string> &GetHints() const;

  /**
   * @brief Checks if the item is forbidden.
   * @return True if the item is forbidden, false otherwise.
   */
  [[nodiscard]] bool IsForbidden() const;

  /**
   * @brief Checks if the item can be transported as registered luggage.
   * @return True if the item can be transported as registered luggage, false otherwise.
   */
  [[nodiscard]] bool IsRegisteredLuggage() const;

  /**
   * @brief Checks if the item can be transported as hand luggage.
   * @return True if the item can be transported as hand luggage, false otherwise.
   */
  [[nodiscard]] bool IsHandLuggage() const;

  /**
   * @brief Checks if the item needs pilot allowance to be transported.
   * @return True if the item needs pilot allowance to be transported, false otherwise.
   */
  [[nodiscard]] bool IsPilotAllowance() const;

  /**
   * @brief Gets the maximum count of the item.
   * @return The maximum count of the item.
   */
  [[nodiscard]] double GetMaxCount() const;

  /**
   * @brief Gets the weight of the item.
   * @return The weight of the item.
   */
  [[nodiscard]] double GetWeight() const;

  /**
   * @brief Gets the category of the item.
   * @return The category of the item.
   */
  [[nodiscard]] std::string GetCategory() const;
};

#endif  // AIRPORT_ITEM_H