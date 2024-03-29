#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../user/User.h"
#include "../flights/FlightConnection.h"

void validFunction(const std::string& titleMessage, const std::string& optionalMessage);
void errorFunction(const std::string& titleMessage, const std::string& optionalMessage);
void logoutFunction();
void seeyaFunction();
std::shared_ptr<ftxui::Element> CreateScreen();
std::shared_ptr<ftxui::Element> CreateUserScreen(const User& user);
std::shared_ptr<ftxui::Element> CreateFlightsScreen(const std::vector<FlightConnection>& connections);

#endif // FUNCTIONS_H
