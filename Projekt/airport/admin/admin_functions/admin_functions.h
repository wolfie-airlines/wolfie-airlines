#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_

#include "../../user/user.h"

void HandleAdminDashboard(User &user);

void AddFlight(User &user);

void AddVerificationQuestion(User &user);

void ManageUsers(User &user);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
