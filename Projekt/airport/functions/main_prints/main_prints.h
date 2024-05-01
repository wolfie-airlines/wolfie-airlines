#ifndef AIRPORT_MAIN_PRINTS_H
#define AIRPORT_MAIN_PRINTS_H

#include <memory>

#include "ftxui/dom/elements.hpp"

void printScreen(const std::shared_ptr<ftxui::Element> &screen);
void printFullWidthScreen(std::shared_ptr<ftxui::Node> container);
void printNodeScreen(std::shared_ptr<ftxui::Node> container);
std::string displayMessageAndCaptureStringInput(const std::string &titleMessage, const std::string &textMessage);
double displayMessageAndCaptureDoubleInput(const std::string &titleMessage, const std::string &textMessage);
std::string displayWarningAndCaptureInput(const std::string &titleMessage, const std::string &textMessage);
#endif  // AIRPORT_MAIN_PRINTS_H
