/**
 * @file helpers.h
 * @brief Ten plik zawiera deklaracje różnych funkcji pomocniczych.
 */

#ifndef AIRPORT_HELPERS_H
#define AIRPORT_HELPERS_H

#include <string>
#include "ftxui/dom/table.hpp"
#include "ftxui/screen/color.hpp"

/**
 * @brief Wyodrębnia nazwę pliku z ścieżki.
 * @param path Ścieżka, z której wyodrębniana jest nazwa pliku.
 * @return Wyodrębniona nazwa pliku.
 */
std::string ExtractFileName(const std::string &path);

/**
 * @brief Wykonuje odliczanie.
 * @param seconds Liczba sekund do odliczenia.
 * @param type Typ odliczania.
 */
void Countdown(int seconds, const std::string &type);

/**
 * @brief Hashuje ciąg znaków.
 * @param string_to_hash Ciąg znaków do zahashowania.
 * @return Zahashowany ciąg znaków.
 */
std::string HashString(const std::string &string_to_hash);

/**
 * @brief Ustawia kolor komórki w tabeli.
 * @param table Tabela zawierająca komórkę.
 * @param col Kolumna komórki.
 * @param row Rząd komórki.
 * @param color Kolor, na który ma zostać ustawiona komórka.
 */
void SetCellColor(ftxui::Table &table, int col, int row, ftxui::Color color);

#endif  // AIRPORT_HELPERS_H