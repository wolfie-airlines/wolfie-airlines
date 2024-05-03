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

bool ValidateFlightId(const std::string &flight_id);
bool ValidateCity(const std::string &city);
bool ValidateDate(const std::string &date);
bool ValidateTime(const std::string &time);
bool ValidatePrice(const std::string &price);
bool ValidateNonEmpty(const std::string &input);
bool ValidateSolution(const std::string &solution);
#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
