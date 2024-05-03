/**
 * @file item_handler.h
 * @brief This file contains the declaration of various item handling functions.
 */

#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include <vector>

#include "../../user/user.h"
#include "item.h"

/**
 * @brief Gets a double value from a BSON document.
 * @param item The BSON document.
 * @param key The key of the value to get.
 * @return The double value.
 */
double GetDoubleValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Gets an array value from a BSON document.
 * @param item The BSON document.
 * @param key The key of the value to get.
 * @return The array value.
 */
std::vector<std::string> GetArrayValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Gets a string value from a BSON document.
 * @param item The BSON document.
 * @param key The key of the value to get.
 * @return The string value.
 */
std::string GetStringValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Gets the items for a user.
 * @param user The user to get the items for.
 * @return The items for the user.
 */
std::vector<Item> GetItems(User &user);

#endif  // ITEM_HANDLER_H