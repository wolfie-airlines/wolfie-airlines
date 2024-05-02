#include "user_settings_handler.h"

#include "../../../functions/info_prints/info_prints.h"
#include "../../professions/user_profession_functions.h"
#include "../user_payments/user_payment_functions.h"
#include "../user_prints/user_prints.h"
#include "../../../functions/main_prints/main_prints.h"

void HandleSettingsOption(User &user) {
  std::string option = CreateSettingsMenu(user);

  if (option == "1") {
    std::string
        newUsername = DisplayMessageAndCaptureStringInput("Zmiana nazwy użytkownika", "Podaj nową nazwę użytkownika:");
    user.ChangeUsername(newUsername);
  } else if (option == "2") {
    std::string newEmail = DisplayMessageAndCaptureStringInput("Zmiana adresu email", "Podaj nowy adres email:");
    user.ChangeEmail(newEmail);
  } else if (option == "3") {
    std::string newPassword = DisplayMessageAndCaptureStringInput("Zmiana hasła", "Podaj nowe hasło:");
    user.ChangePassword(newPassword);
  } else if (option == "4") {
    if (user.profession_ != "brak") {
      PrintErrorMessage("Przecież już masz swój zawód!", "Pracujesz jako " + user.profession_ + ".");
      return;
    }
    HandleProfession(user);
  } else if (option == "5") {
    HandlePaymentOption(user);
  } else if (option == "back") {
    return;
  } else {
    PrintErrorMessage("Nieprawidłowy wybór.", "Nastąpił powrót do głównego menu.");
  }
}
