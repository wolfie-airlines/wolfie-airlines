/**
 * @file main_prints.h
 * @brief Ten plik zawiera deklaracje różnych funkcji wyświetlających i przechwytujących dane wejściowe.
 */

#ifndef AIRPORT_MAIN_PRINTS_H
#define AIRPORT_MAIN_PRINTS_H

#include <memory>

#include "ftxui/dom/elements.hpp"
#include "../../user/user.h"

/**
 * @brief Drukuje ekran.
 * @param screen Ekran do wydrukowania.
 */
void PrintScreen(const std::shared_ptr<ftxui::Element> &screen);

/**
 * @brief Drukuje ekran o pełnej szerokości.
 * @param container Kontener do wydrukowania.
 */
void PrintFullWidthScreen(std::shared_ptr<ftxui::Node> container);

/**
 * @brief Drukuje ekran węzła.
 * @param container Kontener do wydrukowania.
 */
void PrintNodeScreen(std::shared_ptr<ftxui::Node> container);

/**
 * @brief Wyświetla wiadomość i przechwytuje dane wejściowe typu string.
 * @param title_message Tytuł wiadomości.
 * @param text_message Tekst wiadomości.
 * @return Przechwycone dane wejściowe typu string.
 */
std::string DisplayMessageAndCaptureStringInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Wyświetla wiadomość i przechwytuje dane wejściowe typu double.
 * @param title_message Tytuł wiadomości.
 * @param text_message Tekst wiadomości.
 * @return Przechwycone dane wejściowe typu double.
 */
double DisplayMessageAndCaptureDoubleInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Wyświetla ostrzeżenie i przechwytuje dane wejściowe.
 * @param title_message Tytuł wiadomości.
 * @param text_message Tekst wiadomości.
 * @return Przechwycone dane wejściowe.
 */
std::string DisplayWarningAndCaptureInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Wyświetla menu użytkownika.
 * @param user Użytkownik, dla którego wyświetlane jest menu.
 */
void DisplayUserMenu(User &user);

/**
 * @brief Wyświetla główne menu.
 */
void DisplayMenu();

#endif  // AIRPORT_MAIN_PRINTS_H