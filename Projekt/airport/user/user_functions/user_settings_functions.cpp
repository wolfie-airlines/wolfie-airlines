#include "user_settings_functions.h"
#include "../../functions/info_print_functions.h"
#include "user_prints/user_print_functions.h"

void handleSettingsOption(User& user) {
    std::string option = handleSettingsMenu(user);
    if (option== "1") {
        std::string newUsername;
        std::cout << "Podaj nową nazwę użytkownika: ";
        std::cin >> newUsername;
        user.changeUsername(newUsername);
    } else if (option== "2") {
        std::string newEmail;
        std::cout << "Podaj nowego maila: ";
        std::cin >> newEmail;
        user.changeEmail(newEmail);
    } else if (option== "3") {
        std::string newPassword;
        std::cout << "Podaj nowe hasło: ";
        std::cin >> newPassword;
        std::cout << "Powtórz nowe hasło: ";
        std::string repeatedPassword;
        std::cin >> repeatedPassword;
        if (newPassword == repeatedPassword) {
            //TODO: setPassword function()
//            user.setPassword(newPassword);
            validFunction("Hasło zostało zmienione pomyślnie.", "Pamiętaj, żeby nie zapomnieć nowego hasła.");
        } else {
            errorFunction("Podane hasła nie są takie same.", "Spróbuj ponownie.");
        }
    } else if (option== "4") {
        //wszystkie discounty

        //TODO: Wszystko związane ze zniżkami
        //std::vector<Discount> discounts = user.getDiscounts();
        std::cout << "Funkcja w trakcie implementacji." << std::endl;

    } else if (option== "5") {
        //wyświetlenie proffesionScreen
        std::cout << "Funkcja w trakcie implementacji." << std::endl;
    }
    else if (option== "6") {
        //zmiana domyślnej płatności
        std::cout << "Funkcja w trakcie implementacji." << std::endl;
    }
    else if (option== "back") {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}
