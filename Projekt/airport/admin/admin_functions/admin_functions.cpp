#include "admin_functions.h"
#include "../admin.h"
#include "../admin_prints/admin_prints.h"
#include "../../functions/info_prints/info_prints.h"

std::string ProcessAddingFlight() {
  DisplayAddingFlightInfo();
  std::string input;
  std::cin >> input;
  return input;
}

void HandleAdminDashboard(Admin &admin, User &user) {
  DisplayAdminMenu();
  std::string option;
  std::cin >> option;

  while (option != "quit") {
    if (option == "1") {
      admin.AddFlight(user);
    } else if (option == "2") {
      admin.AddVerificationQuestion(user);
    } else if (option == "3") {
      admin.ManageUsers(user);
    } else if (option == "4") {
      admin.AddLuggageItem(user);
    } else {
      PrintErrorMessage("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
    DisplayAdminMenu();
    std::cin >> option;
  }
}

std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator) {
  std::string input = DisplayAdminMessageAndCaptureInput(title, message);
  while (!validator(input)) {
    PrintErrorMessage("Niepoprawne dane", message);
    if (input == "back") {
      PrintErrorMessage("Przerwano działanie administratora.", "Nastąpił powrót do panelu.");
      return "";
    }
    input = DisplayAdminMessageAndCaptureInput(title, message);
  }
  return input;
}

std::string CaptureLineWithValidation(const std::string &title,
                                      const std::string &message,
                                      const std::function<bool(const std::string &)> &validator) {
  std::string input = DisplayAdminMessageAndCaptureLine(title, message);
  while (!validator(input)) {
    PrintErrorMessage("Niepoprawne dane", message);
    if (input == "back") {
      PrintErrorMessage("Przerwano działanie administratora.", "Nastąpił powrót do panelu.");
      return "";
    }
    input = DisplayAdminMessageAndCaptureLine(title, message);
  }
  return input;
}

bool ValidateFlightId(const std::string &flight_id) {
  return !flight_id.empty() && flight_id.length() == 5;
}

bool ValidateCity(const std::string &city) {
  return !city.empty();
}

bool ValidateDate(const std::string &date) {
  return !date.empty() && date.length() == 10 && date[2] == '.' && date[5] == '.';
}

bool ValidateTime(const std::string &time) {
  return !time.empty() && time.length() == 5 && time[2] == ':';
}

bool ValidatePrice(const std::string &price) {
  try {
    int price_int = std::stoi(price);
    return price_int >= 0;
  } catch (std::invalid_argument &e) {
    return false;
  }
}

bool ValidateNonEmpty(const std::string &input) {
  return !input.empty();
}

bool ValidateSolution(const std::string &solution) {
  try {
    return std::stoi(solution) == std::stoi(solution);
  } catch (std::invalid_argument &e) {
    try {
      double solution_double = std::stod(solution);
      return solution_double == solution_double;
    } catch (std::invalid_argument &e) {
      return !solution.empty();
    }
  }
}