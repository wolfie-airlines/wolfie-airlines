/**
 * @file helpers.h
 * @brief This file contains the declaration of various helper functions.
 */

#ifndef AIRPORT_HELPERS_H
#define AIRPORT_HELPERS_H

#include <string>
#include "ftxui/dom/table.hpp"
#include "ftxui/screen/color.hpp"

/**
 * @brief Extracts the file name from a path.
 * @param path The path to extract the file name from.
 * @return The extracted file name.
 */
std::string ExtractFileName(const std::string &path);

/**
 * @brief Performs a countdown.
 * @param seconds The number of seconds to countdown.
 * @param type The type of countdown.
 */
void Countdown(int seconds, const std::string &type);

/**
 * @brief Hashes a string.
 * @param string_to_hash The string to hash.
 * @return The hashed string.
 */
std::string HashString(const std::string &string_to_hash);

/**
 * @brief Sets the color of a cell in a table.
 * @param table The table containing the cell.
 * @param col The column of the cell.
 * @param row The row of the cell.
 * @param color The color to set the cell to.
 */
void SetCellColor(ftxui::Table &table, int col, int row, ftxui::Color color);

#endif  // AIRPORT_HELPERS_H