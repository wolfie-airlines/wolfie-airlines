#include "item.h"

Item::Item(const std::string &item_name, const std::string &description, const std::vector<std::string> &hints,
           bool forbidden, bool registered_luggage, bool hand_luggage, bool pilot_allowance, double max_count,
           double weight, std::string &profession, std::string &category) {
  this->item_name_ = item_name;
  this->description_ = description;
  this->hints_ = hints;
  this->forbidden_ = forbidden;
  this->registered_luggage_ = registered_luggage;
  this->hand_luggage_ = hand_luggage;
  this->pilot_allowance_ = pilot_allowance;
  this->max_count_ = max_count;
  this->weight_ = weight;
  this->profession_ = profession;
  this->category_ = category;
}

Item::Item(const std::string &item_name, const std::string &description, const std::vector<std::string> &hints,
           bool forbidden, bool registered_luggage, bool hand_luggage, bool pilot_allowance, double max_count,
           double weight, std::string &category) {
  this->item_name_ = item_name;
  this->description_ = description;
  this->hints_ = hints;
  this->forbidden_ = forbidden;
  this->registered_luggage_ = registered_luggage;
  this->hand_luggage_ = hand_luggage;
  this->pilot_allowance_ = pilot_allowance;
  this->max_count_ = max_count;
  this->weight_ = weight;
  this->category_ = category;
}

const std::string &Item::GetItemName() const {
  return item_name_;
}

const std::string &Item::GetProfession() const {
  return profession_;
}

const std::string &Item::GetDescription() const {
  return description_;
}

const std::vector<std::string> &Item::GetHints() const {
  return hints_;
}

bool Item::IsForbidden() const {
  return forbidden_;
}

bool Item::IsRegisteredLuggage() const {
  return registered_luggage_;
}

bool Item::IsHandLuggage() const {
  return hand_luggage_;
}

bool Item::IsPilotAllowance() const {
  return pilot_allowance_;
}

double Item::GetMaxCount() const {
  return max_count_;
}

double Item::GetWeight() const {
  return weight_;
}

std::string Item::GetCategory() const {
  return category_;
}