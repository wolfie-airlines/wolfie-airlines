#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H
#include "../authentication/authentication.h"
#include "../flights/flight_connection.h"

void HandleRegistration(Authentication &auth);
bool HandleLogin(Authentication &auth, User &user);
void HandleUserMenu(User &user);
void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection);
void HandleMenu();

#endif  // MAIN_FUNCTIONS_H