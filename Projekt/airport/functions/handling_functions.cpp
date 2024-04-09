#include <iostream>
#include <future>
#include <string>
#include <vector>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../authentication/Authentication.h"
#include "../flights/FlightConnection.h"
#include "info_print_functions.h"
#include "../flights/flights_functions/flight_functions.h"
#include "../user/user_functions/user_prints/user_print_functions.h"
#include "../user/user_functions/user_settings/user_settings_functions.h"
#include "../user/premium_cards/premium_cards.h"

void handleRegistration(Authentication& auth) {
    std::string username, email, password;
    std::cout << "Podaj nazwę użytkownika: ";
    std::cin >> username;
    std::cout << "Podaj email: ";
    std::cin >> email;
    std::cout << "Podaj hasło: ";
    std::cin >> password;
    bool validRegister = auth.registerUser(username, email, password);
    if (validRegister) {
        validFunction("Zarejestrowano pomyślnie.", "Zaloguj się aby kontynuować.");
    } else {
        errorFunction("Rejestracja nie powiodła się.", "Spróbuj ponownie z innymi danymi.");
    }
}

bool handleLogin(Authentication& auth, User& currentUser) {
    std::string username, password;
    std::cout << "Podaj nazwę użytkownika: ";
    std::cin >> username;
    std::cout << "Podaj hasło: ";
    std::cin >> password;
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
    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateUserScreen(currentUser)));
    ftxui::Render(userScreen, *CreateUserScreen(currentUser));
    std::cout << userScreen.ToString() << '\0' << std::endl;
}

void handleMenu() {
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateScreen()));
    ftxui::Render(screen, *CreateScreen());
    std::cout << screen.ToString() << '\0' << std::endl;
}

void handleBuyTicket(FlightConnection& connection, User& user) {
//    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateTicketScreen()));
//    ftxui::Render(screen, *CreateTicketScreen());
//    std::cout << screen.ToString() << '\0' << std::endl;
// TODO
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
                handleFlightOptions(flightConnection);
            } else if (choice == "4") {
                errorFunction("Musisz być zalogowany aby kupić bilet.", "Zaloguj się aby kontynuować.");
            }
            else if (choice == "quit") {
                seeyaFunction();
                break;
            } else {
                errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
            }
        } else {
            handleUserMenu(currentUser);
            std::string userChoice;
            std::cin >> userChoice;
            if(userChoice == "settings") {
                handleSettingsOption(currentUser);
            }
            else if(userChoice == "profil") {
                std::string backOption = CreateProfileScreen(currentUser);
                if(backOption == "back") {
                    handleUserMenu(currentUser);
                }
            }
            else if (userChoice == "logout") {
                logoutFunction();
                isLoggedIn = false;
            } else if(userChoice == "1") {
                handleFlightOptions(flightConnection);
            }
            else if(userChoice == "2") {
                handleBuyTicket(flightConnection, currentUser);
            }
            else if(userChoice == "3") {
                handlePremiumCard(currentUser);
            }
        }
    }
}


