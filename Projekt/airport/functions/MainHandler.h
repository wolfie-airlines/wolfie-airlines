#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H
#include "../authentication/Authentication.h"
#include "../flights/FlightConnection.h"

void handleRegistration(Authentication &auth);
bool handleLogin(Authentication &auth, User &currentUser);
void handleUserMenu(User &currentUser);
void processChoice(bool isLoggedIn, Authentication &auth, User &currentUser, FlightConnection &flightConnection);
void handleMenu();

#endif  // MAIN_FUNCTIONS_H