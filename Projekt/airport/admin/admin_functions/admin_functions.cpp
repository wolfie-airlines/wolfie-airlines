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

std::optional<bool> CaptureBoolWithValidation(const std::string &title, const std::string &message) {
  while (true) {
    std::string input = CaptureInputWithValidation(title, message, [](const std::string &input) {
      return input == "tak" || input == "nie" || input == "back";
    });
    if (input == "back") {
      PrintErrorMessage("Przerwano dodawanie przedmiotu", "Nastąpił powrót do panelu.");
      return std::nullopt;
    }
    if (input == "tak") return true;
    if (input == "nie") return false;
  }
}