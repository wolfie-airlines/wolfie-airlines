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
    std::string item_name = GetStringValue(item, "item");
    std::string description = GetStringValue(item, "description");
    std::vector<std::string> hints = GetArrayValue(item, "hints");
    bool forbidden = item["forbidden"].get_bool().value;
    bool registered_luggage = item["registered_luggage"].get_bool().value;
    bool hand_luggage = item["hand_luggage"].get_bool().value;
    bool pilot_allowance = item["pilot_allowance"].get_bool().value;
    double max_count = GetDoubleValue(item, "max_count");
    double weight = GetDoubleValue(item, "weightForOne");
    std::string profession = GetStringValue(item, "profession");
    std::string category = GetStringValue(item, "category");

    if (profession.empty()) {
      category = category.empty() ? "special" : category;
      items.emplace_back(item_name,
                         description,
                         hints,
                         forbidden,
                         registered_luggage,
                         hand_luggage,
                         pilot_allowance,
                         max_count,
                         weight,
                         category);
    } else {
      items.emplace_back(item_name,
                         description,
                         hints,
                         forbidden,
                         registered_luggage,
                         hand_luggage,
                         pilot_allowance,
                         max_count,
                         weight,
                         profession,
                         category);
    }
  }

  return items;
}