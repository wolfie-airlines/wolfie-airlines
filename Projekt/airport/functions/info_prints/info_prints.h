#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "../../user/user.h"

void PrintSuccessMessage(const std::string &title_message, const std::string &optional_message);
void PrintErrorMessage(const std::string &title_message, const std::string &optional_message);
void PrintLogout(User &user);
void PrintSeeya();

#endif  // FUNCTIONS_H
