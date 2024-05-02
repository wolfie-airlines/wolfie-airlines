#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "../../user/user.h"

void PrintSuccessMessage(const std::string &titleMessage, const std::string &optionalMessage);
void PrintErrorMessage(const std::string &titleMessage, const std::string &optionalMessage);
void PrintLogout(User &user);
void PrintSeeya();

#endif  // FUNCTIONS_H
