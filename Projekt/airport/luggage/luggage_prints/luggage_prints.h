#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H

#include "../../user/user.h"
#include "../item/item.h"
#include "ftxui/component/component.hpp"

const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";
const std::string ITEM_CARD = "KARTA PRZEDMIOTU";

std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components);
void PrintAllItems(User &user);
void PrintSpecificItem(Item &item);
void PrintWelcomeInCheckIn(User &user);

#endif  // AIRPORT_LUGGAGE_PRINTS_H
