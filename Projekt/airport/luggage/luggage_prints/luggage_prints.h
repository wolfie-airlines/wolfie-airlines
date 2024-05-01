#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H

#include "../../user/User.h"
#include "../item/Item.h"
#include "ftxui/component/component.hpp"

std::vector<ftxui::Component> createGroups(const std::vector<ftxui::Component> &checkbox_components);
void printAllItems(User &user);
void printSpecificItem(Item &item);

#endif  // AIRPORT_LUGGAGE_PRINTS_H
