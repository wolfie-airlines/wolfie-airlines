#include "user_settings_functions.h"
#include "../../functions/info_print_functions.h"
#include "user_prints/user_print_functions.h"

void handlePaymentOption(User& user) {
    int answer = CreateDefaultPaymentScreen();
    if (answer == 0) {
        // zmiana na VISĘ
        std::cout << "Podaj 3 ostatnie cyfry karty: ";
        std::string cardNumber;
        std::cin >> cardNumber;
        std::cout << "Podaj kod CVV karty: ";
        std::string cvv;
        std::cin >> cvv;
        user.setPaymentMethod("visa");
        user.handleVisa(cardNumber, cvv);
    } else if (answer == 1) {
        user.setPaymentMethod("blik");
    } else if(answer == 3 ) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}

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
        user.changePassword(newPassword);
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
        handlePaymentOption(user);
    }
    else if (option== "back") {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Nastąpił powrót do głównego menu.");
    }
}


