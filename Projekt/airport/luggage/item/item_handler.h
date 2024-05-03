#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include <vector>

#include "../../user/user.h"
#include "item.h"

double GetDoubleValue(const bsoncxx::document::view &item, const std::string &key);
std::vector<std::string> GetArrayValue(const bsoncxx::document::view &item, const std::string &key);
std::string GetStringValue(const bsoncxx::document::view &item, const std::string &key);
std::vector<Item> GetItems(User &user);

#endif  // ITEM_HANDLER_H