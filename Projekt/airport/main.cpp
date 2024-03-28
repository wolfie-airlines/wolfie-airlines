#include <cstdlib>
#include <iostream>
#include <future>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include <bsoncxx/builder/basic/document.hpp>
#include "EnvParser.h"
#include "Authentication.h"
#include "printFunctions.h"

int main(int argc, char* argv[]) {
    mongocxx::instance inst;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    EnvParser parser;
    parser.parseEnvFile();

    try {
        const auto uri_str = (argc >= 2) ? argv[1] : parser.getValue("DATABASE_URL");
        auto uri = mongocxx::uri{uri_str};

        mongocxx::client client{uri};

        Authentication auth{uri_str, "projekt", "users"};

        auto db = client["projekt"];
        auto collection = db["connection_test"];

        // testowy dokument dla pingu do kolekcji
        auto result = collection.insert_one(make_document(kvp("ping", 1)));

        if (!result) {
            std::cout << "Nie udalo sie..." << std::endl;
            return EXIT_FAILURE;
        }

        bool isLoggedIn = false;
        User currentUser;
        while (true) {
            if (!isLoggedIn) {
                auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateScreen()));
                ftxui::Render(screen, *CreateScreen());
                std::cout << screen.ToString() << '\0' << std::endl;

                std::string choice;
                std::cin >> choice;

                if (choice == "1") {
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
                } else if (choice == "2") {
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
                        isLoggedIn = true;
                    }else {
                        errorFunction("Logowanie nie powiodło się.", "Spróbuj ponownie z innymi danymi.");
                    }
                } else if (choice == "quit") {
                    seeyaFunction();
                    break;
                } else {
                    errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
                }
            } else {
                auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateUserScreen(currentUser)));
                ftxui::Render(userScreen, *CreateUserScreen(currentUser));
                std::cout << userScreen.ToString() << '\0' << std::endl;

                std::string userChoice;
                std::cin >> userChoice;
                if (userChoice == "logout") {
                    logoutFunction();
                    isLoggedIn = false;
                }
            }
        }
    } catch (const std::exception& ex) {
        std::cout << "Blad operacji: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // Wyjście z programu
}