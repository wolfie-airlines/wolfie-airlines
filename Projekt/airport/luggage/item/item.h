//
// Created by szymo on 26.04.2024.
//

#ifndef AIRPORT_ITEM_H
#define AIRPORT_ITEM_H

#include <string>
#include <vector>

class User;

class Item {
  std::string item_name_;
  std::string description_;
  std::vector<std::string> hints_;
  bool forbidden_;
  bool registered_luggage_;
  bool hand_luggage_;
  bool pilot_allowance_;
  double max_count_;
  double weight_;
  std::string profession_;
  std::string category_ = "special";

 public:
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

  [[nodiscard]] const std::string &GetItemName() const;

  [[nodiscard]] const std::string &GetDescription() const;

  [[nodiscard]] const std::string &GetProfession() const;

  [[nodiscard]] const std::vector<std::string> &GetHints() const;

  [[nodiscard]] bool IsForbidden() const;

  [[nodiscard]] bool IsRegisteredLuggage() const;

  [[nodiscard]] bool IsHandLuggage() const;

  [[nodiscard]] bool IsPilotAllowance() const;

  [[nodiscard]] double GetMaxCount() const;

  [[nodiscard]] double GetWeight() const;

  [[nodiscard]] std::string GetCategory() const;
};

#endif  // AIRPORT_ITEM_H
