/**
 * @file luggage_prints.h
 * @brief This file contains the declaration of various luggage handling functions.
 */

#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H

#include "../../user/user.h"
#include "../item/item.h"
#include "ftxui/component/component.hpp"

const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈"; ///< The name of the airport.
const std::string ITEM_CARD = "KARTA PRZEDMIOTU"; ///< The item card.

/**
 * @brief Creates groups of components.
 * @param checkbox_components The components to group.
 * @return The groups of components.
 */
std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components);

/**
 * @brief Prints all items for a user.
 * @param user The user to print the items for.
 */
void PrintAllItems(User &user);

/**
 * @brief Prints a specific item.
 * @param item The item to print.
 */
void PrintSpecificItem(Item &item);

/**
 * @brief Prints a welcome message in the check-in.
 * @param user The user to print the welcome message for.
 */
void PrintWelcomeInCheckIn(User &user);

#endif  // AIRPORT_LUGGAGE_PRINTS_H