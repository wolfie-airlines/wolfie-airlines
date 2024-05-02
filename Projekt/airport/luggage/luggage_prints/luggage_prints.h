#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H

#include "../../user/user.h"
#include "../item/item.h"
#include "ftxui/component/component.hpp"

std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components);
void PrintAllItems(User &user);
void PrintSpecificItem(Item &item);

#endif  // AIRPORT_LUGGAGE_PRINTS_H
