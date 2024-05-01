#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include "Item.h"
#include "../../user/User.h"
#include <vector>

double getDoubleValue(const bsoncxx::document::view& item, const std::string& key);
std::vector<std::string> getArrayValue(const bsoncxx::document::view& item, const std::string& key);
std::string getStringValue(const bsoncxx::document::view& item, const std::string& key);
std::vector<Item> getItems(User& user);

#endif // ITEM_HANDLER_H