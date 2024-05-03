#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_

#include "../../user/user.h"

void HandleAdminDashboard(Admin &admin, User &user);

std::string ProcessAddingFlight();

std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

std::string CaptureLineWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

std::optional<bool> CaptureBoolWithValidation(const std::string &title, const std::string &message);
#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
