/**
 * @file item_handler.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących przedmioty.
 */

#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include <vector>

#include "../../user/user.h"
#include "item.h"

/**
 * @brief Pobiera wartość typu double z dokumentu BSON.
 * @param item Dokument BSON.
 * @param key Klucz wartości do pobrania.
 * @return Wartość typu double.
 */
double GetDoubleValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Pobiera wartość tablicy z dokumentu BSON.
 * @param item Dokument BSON.
 * @param key Klucz wartości do pobrania.
 * @return Wartość tablicy.
 */
std::vector<std::string> GetArrayValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Pobiera wartość typu string z dokumentu BSON.
 * @param item Dokument BSON.
 * @param key Klucz wartości do pobrania.
 * @return Wartość typu string.
 */
std::string GetStringValue(const bsoncxx::document::view &item, const std::string &key);

/**
 * @brief Pobiera przedmioty dla użytkownika.
 * @param user Użytkownik, dla którego pobierane są przedmioty.
 * @return Przedmioty dla użytkownika.
 */
std::vector<Item> GetItems(User &user);

#endif  // ITEM_HANDLER_H