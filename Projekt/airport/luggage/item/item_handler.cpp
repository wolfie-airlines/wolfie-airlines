#include "item_handler.h"

double getDoubleValue(const bsoncxx::document::view &item, const std::string &key) {
  if (item[key].type() == bsoncxx::type::k_double) {
    return item[key].get_double().value;
  } else {
    return static_cast<double>(item[key].get_int32().value);
  }
}

std::vector<std::string> getArrayValue(const bsoncxx::document::view &item, const std::string &key) {
  std::vector<std::string> array;
  if (item[key]) {
    for (const auto &element : item[key].get_array().value) {
      array.push_back((std::string) element.get_string().value);
    }
  }
  return array;
}

std::string getStringValue(const bsoncxx::document::view &item, const std::string &key) {
  if (item[key]) {
    return (std::string) item[key].get_string().value;
  }
  return "";
}

std::vector<Item> getItems(User &user) {
  auto collection = user.getSpecificCollection("luggage_list");
  auto cursor = collection.find({});

  std::vector<Item> items;
  for (const auto &item : cursor) {
    std::string itemName = getStringValue(item, "item");
    std::string description = getStringValue(item, "description");
    std::vector<std::string> hints = getArrayValue(item, "hints");
    bool forbidden = item["forbidden"].get_bool().value;
    bool registeredLuggage = item["registeredLuggage"].get_bool().value;
    bool handLuggage = item["handLuggage"].get_bool().value;
    bool pilotAllowance = item["pilotAllowance"].get_bool().value;
    double maxCount = getDoubleValue(item, "maxCount");
    double weight = getDoubleValue(item, "weightForOne");
    std::string profession = getStringValue(item, "profession");
    std::string category = getStringValue(item, "category");

    if (profession.empty()) {
      category = category.empty() ? "special" : category;
      items.emplace_back(itemName,
                         description,
                         hints,
                         forbidden,
                         registeredLuggage,
                         handLuggage,
                         pilotAllowance,
                         maxCount,
                         weight,
                         category);
    } else {
      items.emplace_back(itemName,
                         description,
                         hints,
                         forbidden,
                         registeredLuggage,
                         handLuggage,
                         pilotAllowance,
                         maxCount,
                         weight,
                         profession,
                         category);
    }
  }

  return items;
}