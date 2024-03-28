#include <cstdlib>
#include <iostream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include <bsoncxx/builder/basic/document.hpp>
#include "EnvParser.h"
#include "Authentication.h"
#include "functions.h"

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

        auto summary = [&] {
            auto content = ftxui::vbox({
                                        ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold}) | color(ftxui::Color::Blue),
                                        ftxui::hbox({ftxui::text(L"1. Zarejestruj się   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                        ftxui::hbox({ftxui::text(L"2. Zaloguj się   ")  | ftxui::bold}) | color(ftxui::Color::GrayDark),

                                        ftxui::separator(),
                                        ftxui::hbox({ftxui::text(L"Wprowadź numer akcji, którą chcesz wykonać poniżej:")  | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                });
            return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
        };

        auto document = ftxui::vbox({summary()});

        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

        auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
        Render(screen, document);

        std::cout << screen.ToString() << '\0' << std::endl;

        std::string choice;
        std::cin >> choice;

        while(true) {
            if(choice == "quit" || choice == "cancel" || choice == "exit") {
                break;
            }
            else if (choice == "1") {
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
                auth.authenticateUser(username, password);
            } else {
                errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
            }
        }

    } catch (const std::exception& ex) {
        std::cout << "Blad operacji: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}
