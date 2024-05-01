#include <future>
#include <iostream>
#include <string>
#include <vector>

#include "../authentication/Authentication.h"
#include "../authentication/auth_functions/AuthPrintHandler.h"
#include "../checkin/checkin_functions_prints.h"
#include "../flights/flights_functions/flight_functions.h"
#include "../luggage/LuggageHandler.h"
#include "../tickets/tickets.h"
#include "../tickets/tickets_prints/tickets_print_functions.h"
#include "../user/discounts/discounts.h"
#include "../user/premium_cards/premium_cards.h"
#include "../user/user_functions/user_prints/user_print_functions.h"
#include "../user/user_functions/user_settings/user_settings_handler.h"
#include "../user/user_functions/user_tickets/user_tickets_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "info_print_functions.h"

void handleRegistration(Authentication& auth) {
    std::string username, email, password;
    bool cancelled;

    std::tie(username, email, password, cancelled) = registerUser();

    if (username.empty() && !cancelled) {
        errorFunction("Nie podano nazwy użytkownika.", "Spróbuj ponownie.");
        return;
    }

    if (email.empty() && !cancelled) {
        errorFunction("Nie podano adresu e-mail.", "Spróbuj ponownie.");
        return;
    }

    if (password.empty() && !cancelled) {
        errorFunction("Nie podano hasła.", "Spróbuj ponownie.");
        return;
    }

    if (cancelled) {
        errorFunction("Rejestracja anulowana.", "Zawsze możesz ponowić próbę.");
        return;
    }

    bool validRegister = auth.registerUser(username, email, password);

    if (validRegister) {
        validFunction("Zarejestrowano pomyślnie.", "Zaloguj się aby kontynuować.");
    } else {
        errorFunction("Rejestracja nie powiodła się.", "Spróbuj ponownie.");
    }
}

bool handleLogin(Authentication& auth, User& currentUser) {
    std::string username, password;
    bool cancelled;
    std::tuple<std::string, std::string, bool> loginData = login();
    std::tie(username, password, cancelled) = loginData;

    if (username.empty() && !cancelled) {
        errorFunction("Nie podano nazwy użytkownika.", "Spróbuj ponownie.");
        return false;
    }

    if (password.empty() && !cancelled) {
        errorFunction("Nie podano hasła.", "Spróbuj ponownie.");
        return false;
    }

    if (cancelled) {
        errorFunction("Logowanie anulowane.", "Zawsze możesz ponowić próbę.");
        return false;
    }

    std::promise<bool> promise;

    auth.authenticateUser(username, password, std::move(promise), currentUser);
    std::future<bool> future = promise.get_future();

    bool validLogin = future.get();

    if (validLogin) {
        return true;
    } else {
        errorFunction("Logowanie nie powiodło się.", "Spróbuj ponownie z innymi danymi.");
        return false;
    }
}

void handleUserMenu(User& currentUser) {
    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateUserMenu(currentUser)));
    ftxui::Render(userScreen, *CreateUserMenu(currentUser));
    std::cout << userScreen.ToString() << '\0' << std::endl;
}

void handleMenu() {
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateDefaultMenu()));
    ftxui::Render(screen, *CreateDefaultMenu());
    std::cout << screen.ToString() << '\0' << std::endl;
}

void processChoice(bool isLoggedIn, Authentication& auth, User& currentUser, FlightConnection& flightConnection) {
    while (true) {
        if (!isLoggedIn) {
            handleMenu();
            std::string choice;
            std::cin >> choice;

            if (choice == "1") {
                handleRegistration(auth);
            } else if (choice == "2") {
                if (handleLogin(auth, currentUser)) {
                    isLoggedIn = true;
                }
            } else if (choice == "3") {
                handleFlightOptions(flightConnection, currentUser);
            } else if (choice == "4") {
                errorFunction("Musisz być zalogowany aby kupić bilet.", "Zaloguj się aby kontynuować.");
            } else if (choice == "5") {
                openWebsite();
            } else if (choice == "quit") {
                seeyaFunction();
                break;
            } else {
                errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
            }
        } else {
            handleUserMenu(currentUser);
            std::string userChoice;
            std::cin >> userChoice;
            if (userChoice == "settings") {
                handleSettingsOption(currentUser);
            } else if (userChoice == "profil") {
                CreateProfileScreen(currentUser);
            } else if (userChoice == "logout") {
                logoutFunction(currentUser);
                isLoggedIn = false;
            } else if (userChoice == "1") {
                handleFlightOptions(flightConnection, currentUser);
            } else if (userChoice == "2") {
                handleTicketChoice(flightConnection, currentUser);
            } else if (userChoice == "3") {
                if (currentUser.discountType == "ulga") {
                    errorFunction("Nie możesz zakupić karty premium.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
                } else {
                    handlePremiumCard(currentUser);
                }
            } else if (userChoice == "4") {
                if (currentUser.discountType == "premium") {
                    errorFunction("Nie możesz starać się o ulgę.", "Posiadasz już zniżki z karty premium.");
                } else if (currentUser.discountType == "ulga") {
                    errorFunction("Nie możesz starać się o ulgę.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
                } else {
                    printDiscountCard(currentUser);
                }
            } else if (userChoice == "5") {
                createTicketsScreen(currentUser);
            } else if (userChoice == "6") {
                printCheckinScreen(currentUser);
            } else if (userChoice == "7") {
                welcomeInLuggageCheckin(currentUser);
            } else if (userChoice == "8") {
                currentUser.loginAsAdmin();
            }
        }
    }
}
