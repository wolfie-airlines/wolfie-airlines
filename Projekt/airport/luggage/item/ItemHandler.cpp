#include "ItemHandler.h"

std::vector<Item> getItems(User& user) {
    auto collection = user.getSpecificCollection("luggage_list");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto &&doc: cursor) {
        documents.push_back(doc);
    }

    std::vector<Item> items;
    for (const auto& item : documents) {
        std::string itemName = (std::string) item["item"].get_string().value;

        std::string description;
        if(item["description"]) {
            description = (std::string) item["description"].get_string().value;
        }

        std::vector<std::string> hints;
        if(item["hints"]) {
            for (const auto& hint : item["hints"].get_array().value) {
                hints.push_back((std::string) hint.get_string().value);
            }
        }

        bool forbidden = item["forbidden"].get_bool().value;
        bool registeredLuggage = item["registeredLuggage"].get_bool().value;
        bool handLuggage = item["handLuggage"].get_bool().value;
        bool pilotAllowance = item["pilotAllowance"].get_bool().value;
        double maxCount;
        if (item["maxCount"].type() == bsoncxx::type::k_double) {
            maxCount = item["maxCount"].get_double().value;
        } else {
            maxCount = static_cast<double>(item["maxCount"].get_int32().value);
        }

        double weight;
        if (item["weightForOne"].type() == bsoncxx::type::k_double) {
            weight = item["weightForOne"].get_double().value;
        } else {
            weight = static_cast<double>(item["weightForOne"].get_int32().value);
        }
        items.emplace_back(
                itemName, description, hints, forbidden, registeredLuggage, handLuggage, pilotAllowance, maxCount, weight
        );
    }

    return items;
}