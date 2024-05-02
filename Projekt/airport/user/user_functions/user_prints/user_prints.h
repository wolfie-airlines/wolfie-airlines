#ifndef AIRPORT_USER_PRINT_FUNCTIONS_H
#define AIRPORT_USER_PRINT_FUNCTIONS_H

#include <string>

#include "../../user.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

std::shared_ptr<ftxui::Element> CreateDefaultMenu();
std::shared_ptr<ftxui::Element> CreateUserMenu(const User &user);
std::string CreateSettingsMenu(const User &user);
int CreateDefaultPaymentScreen();
void CreateProfileScreen(User &user);

#endif  // AIRPORT_USER_PRINT_FUNCTIONS_H
