#ifndef AIRPORT_USER_PRINT_FUNCTIONS_H
#define AIRPORT_USER_PRINT_FUNCTIONS_H

#include <string>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../../User.h"

std::shared_ptr<ftxui::Element> CreateScreen();
std::shared_ptr<ftxui::Element> CreateUserScreen(const User& user);
std::string handleSettingsMenu(const User& user);


#endif //AIRPORT_USER_PRINT_FUNCTIONS_H
