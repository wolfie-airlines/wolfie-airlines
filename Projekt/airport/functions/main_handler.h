#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "../authentication/authentication.h"
#include "../flights/flight_connection.h"

void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection);

#endif  // MAIN_FUNCTIONS_H