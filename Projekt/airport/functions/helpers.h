#ifndef AIRPORT_HELPERS_H
#define AIRPORT_HELPERS_H
#include <string>
#include "ftxui/dom/table.hpp"
#include "ftxui/screen/color.hpp"

std::string ExtractFileName(const std::string &path);
void Countdown(int seconds, const std::string &type);
std::string HashString(const std::string &string_to_hash);
void SetCellColor(ftxui::Table &table, int col, int row, ftxui::Color color);

#endif  // AIRPORT_HELPERS_H
