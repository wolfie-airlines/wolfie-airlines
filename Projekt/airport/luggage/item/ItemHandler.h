#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include <vector>

#include "../../user/User.h"
#include "Item.h"

double getDoubleValue(const bsoncxx::document::view &item, const std::string &key);
std::vector<std::string> getArrayValue(const bsoncxx::document::view &item, const std::string &key);
std::string getStringValue(const bsoncxx::document::view &item, const std::string &key);
std::vector<Item> getItems(User &user);

#endif  // ITEM_HANDLER_H