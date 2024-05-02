#ifndef AIRPORT_MAIN_PRINTS_H
#define AIRPORT_MAIN_PRINTS_H

#include <memory>

#include "ftxui/dom/elements.hpp"

void PrintScreen(const std::shared_ptr<ftxui::Element> &screen);
void PrintFullWidthScreen(std::shared_ptr<ftxui::Node> container);
void PrintNodeScreen(std::shared_ptr<ftxui::Node> container);
std::string DisplayMessageAndCaptureStringInput(const std::string &titleMessage, const std::string &textMessage);
double DisplayMessageAndCaptureDoubleInput(const std::string &titleMessage, const std::string &textMessage);
std::string DisplayWarningAndCaptureInput(const std::string &titleMessage, const std::string &textMessage);
#endif  // AIRPORT_MAIN_PRINTS_H
