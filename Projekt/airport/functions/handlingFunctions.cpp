#include <iostream>
#include <future>
#include <string>
#include <vector>
#include "ftxui/screen/screen.hpp"
#include "ftxui/dom/elements.hpp"
#include "../authentication/Authentication.h"
#include "../flights/FlightConnection.h"
#include "printFunctions.h"

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

void handleFlightOptions(FlightConnection& flightConnection) {
    std::cout << "Chciałbyś zobaczyć listę wszystkich lotów?" << std::endl;
    std::cout << "Wpisz 'tak' lub 'nie'." << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "tak") {
        //wszystkie możliwe loty
        std::vector<FlightConnection> connections = flightConnection.findAllConnections();
        auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateFlightsScreen(connections)));
        ftxui::Render(userScreen, *CreateFlightsScreen(connections));
        std::cout << userScreen.ToString() << '\0' << std::endl;

    } else if (answer == "nie") {
        //wybór lotów
        std::string departureCity, destinationCity;
        std::cout << "Podaj miasto wylotu: ";
        std::cin >> departureCity;
        std::cout << "Podaj miasto przylotu: ";
        std::cin >> destinationCity;

        FlightConnection connection = flightConnection.findConnection(departureCity, destinationCity);

        std::cout << connection.getDepartureCity() << " -> " << connection.getDestinationCity() << " | " << connection.getDepartureTime() << " -> " << connection.getArrivalTime() << " | " << connection.getPrice() << std::endl;
        std::cout << departureCity << " -> " << destinationCity << std::endl;

        if (connection.getDepartureCity() == departureCity && connection.getDestinationCity() == destinationCity) {
            std::cout << connection.getDepartureCity() << " -> " << connection.getDestinationCity() << " | " << connection.getDepartureTime() << " -> " << connection.getArrivalTime() << " | " << connection.getPrice() << std::endl;
        } else {
            errorFunction("Nie znaleziono takiego lotu.", "Spróbuj ponownie.");
        }
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
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
            if (userChoice == "logout") {
                logoutFunction();
                isLoggedIn = false;
            }
        }
    }
}


