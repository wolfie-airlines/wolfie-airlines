#include "user_settings_handler.h"

#include "../../../functions/info_prints/info_prints.h"
#include "../../professions/user_profession_functions.h"
#include "../user_payments/user_payment_functions.h"
#include "../user_prints/user_prints.h"

void handleSettingsOption(User &user) {
  std::string option = CreateSettingsMenu(user);
  if (option == "1") {
    std::string newUsername;
    std::cout << "Podaj nową nazwę użytkownika: ";
    std::cin >> newUsername;
    user.changeUsername(newUsername);
  } else if (option == "2") {
    std::string newEmail;
    std::cout << "Podaj nowego maila: ";
    std::cin >> newEmail;
    user.changeEmail(newEmail);
  } else if (option == "3") {
    std::string newPassword;
    std::cout << "Podaj nowe hasło: ";
    std::cin >> newPassword;
    user.changePassword(newPassword);
  } else if (option == "4") {
    if (user.profession_ != "brak") {
      errorFunction("Przecież już masz swój zawód!", "Pracujesz jako " + user.profession_ + ".");
      return;
    }
    handleProfession(user);
  } else if (option == "5") {
    handlePaymentOption(user);
  } else if (option == "back") {
    return;
  } else {
    errorFunction("Nieprawidłowy wybór.", "Nastąpił powrót do głównego menu.");
  }
}
