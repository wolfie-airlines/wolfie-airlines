#include "user_settings_handler.h"

#include "../../../functions/info_prints/info_prints.h"
#include "../../../functions/main_prints/main_prints.h"
#include "../../professions/user_profession_functions.h"
#include "../user_payments/user_payment_functions.h"
#include "../user_prints/user_prints.h"

void HandleSettingsOption(User &user) {
    std::string option = DisplaySettingsMenu(user);

    if (option == "1") {
        std::string
            new_username = DisplayMessageAndCaptureStringInput("Changing your username", "Enter a new username:");
        user.ChangeUsername(new_username);
    } else if (option == "2") {
        std::string new_email = DisplayMessageAndCaptureStringInput("Change of email address", "Enter a new email address:");
        user.ChangeEmail(new_email);
    } else if (option == "3") {
        std::string new_password = DisplayMessageAndCaptureStringInput("Password change", "Enter a new password:");
        user.ChangePassword(new_password);
    } else if (option == "4") {
        if (user.profession_ != "none") {
            PrintErrorMessage("After all, you already have your profession!", "You work as " + user.profession_ + ".");
            return;
        }
        HandleProfession(user);
    } else if (option == "5") {
        HandlePaymentOption(user);
    } else if (option == "back") {
        return;
    } else {
        PrintErrorMessage("Incorrect choice.", "There was a return to the main menu.");
    }
}
