/**
 * @file luggage_prints.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących bagaż.
 */

#ifndef AIRPORT_LUGGAGE_PRINTS_H
#define AIRPORT_LUGGAGE_PRINTS_H

#include "../../user/user.h"
#include "../item/item.h"
#include "ftxui/component/component.hpp"

const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈"; ///< Nazwa lotniska.
const std::string ITEM_CARD = "KARTA PRZEDMIOTU"; ///< Karta przedmiotu.

/**
 * @brief Tworzy grupy komponentów.
 * @param checkbox_components Komponenty do pogrupowania.
 * @return Grupy komponentów.
 */
std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components);

/**
 * @brief Drukuje wszystkie przedmioty dla użytkownika.
 * @param user Użytkownik, dla którego drukowane są przedmioty.
 */
void PrintAllItems(User &user);

/**
 * @brief Drukuje konkretny przedmiot.
 * @param item Przedmiot do wydrukowania.
 */
void PrintSpecificItem(Item &item);

/**
 * @brief Drukuje powitanie przy odprawie.
 * @param user Użytkownik, dla którego drukowane jest powitanie.
 */
void PrintWelcomeInCheckIn(User &user);

#endif  // AIRPORT_LUGGAGE_PRINTS_H