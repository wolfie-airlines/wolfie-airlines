#include "item_handler.h"

double GetDoubleValue(const bsoncxx::document::view &item, const std::string &key) {
  if (item[key].type() == bsoncxx::type::k_double) {
    return item[key].get_double().value;
  } else {
    return static_cast<double>(item[key].get_int32().value);
  }
}

std::vector<std::string> GetArrayValue(const bsoncxx::document::view &item, const std::string &key) {
  std::vector<std::string> array;
  if (item[key]) {
    for (const auto &element : item[key].get_array().value) {
      array.push_back((std::string) element.get_string().value);
    }
  }
  return array;
}

std::string GetStringValue(const bsoncxx::document::view &item, const std::string &key) {
  if (item[key]) {
    return (std::string) item[key].get_string().value;
  }
  return "";
}

std::vector<Item> GetItems(User &user) {
  auto collection = user.GetSpecificCollection("luggage_list");
  auto cursor = collection.find({});

  std::vector<Item> items;
  for (const auto &item : cursor) {
    std::string itemName = GetStringValue(item, "item");
    std::string description = GetStringValue(item, "description");
    std::vector<std::string> hints = GetArrayValue(item, "hints");
    bool forbidden = item["forbidden"].get_bool().value;
    bool registeredLuggage = item["registeredLuggage"].get_bool().value;
    bool handLuggage = item["handLuggage"].get_bool().value;
    bool pilotAllowance = item["pilotAllowance"].get_bool().value;
    double maxCount = GetDoubleValue(item, "maxCount");
    double weight = GetDoubleValue(item, "weightForOne");
    std::string profession = GetStringValue(item, "profession");
    std::string category = GetStringValue(item, "category_");

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