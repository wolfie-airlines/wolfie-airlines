#include "item.h"

Item::Item(const std::string &itemName, const std::string &description, const std::vector<std::string> &hints,
           bool forbidden, bool registeredLuggage, bool handLuggage, bool pilotAllowance, double maxCount,
           double weight, std::string &profession, std::string &category) {
  this->itemName = itemName;
  this->description = description;
  this->hints = hints;
  this->forbidden = forbidden;
  this->registeredLuggage = registeredLuggage;
  this->handLuggage = handLuggage;
  this->pilotAllowance = pilotAllowance;
  this->maxCount = maxCount;
  this->weight = weight;
  this->profession = profession;
  this->category = category;
}

Item::Item(const std::string &itemName, const std::string &description, const std::vector<std::string> &hints,
           bool forbidden, bool registeredLuggage, bool handLuggage, bool pilotAllowance, double maxCount,
           double weight, std::string &category) {
  this->itemName = itemName;
  this->description = description;
  this->hints = hints;
  this->forbidden = forbidden;
  this->registeredLuggage = registeredLuggage;
  this->handLuggage = handLuggage;
  this->pilotAllowance = pilotAllowance;
  this->maxCount = maxCount;
  this->weight = weight;
  this->category = category;
}

const std::string &Item::getItemName() const {
  return itemName;
}

const std::string &Item::getProfession() const {
  return profession;
}

const std::string &Item::getDescription() const {
  return description;
}

const std::vector<std::string> &Item::getHints() const {
  return hints;
}

bool Item::isForbidden() const {
  return forbidden;
}

bool Item::isRegisteredLuggage() const {
  return registeredLuggage;
}

bool Item::isHandLuggage() const {
  return handLuggage;
}

bool Item::isPilotAllowance() const {
  return pilotAllowance;
}

double Item::getMaxCount() const {
  return maxCount;
}

double Item::getWeight() const {
  return weight;
}

std::string Item::getCategory() const {
  return category;
}