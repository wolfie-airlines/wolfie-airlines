#include "user_profession_functions.h"
#include "prints/profession_prints.h"

void handleProfessionChoice(int choice) {
    if(choice==0) {
        //Muzyk
    } else if(choice == 1) {
        // Lekarz
    } else if(choice == 1) {
        //Sportowiec
        // Dodatkowe menu dla wyboru dyscypliny
    } else if (choice==2) {
        // Matematyk
    } else if (choice == 3) {
        // Informatyk
    } else {
        return;
    }
}

void handleProfession(User& user) {
    std::string option = displayProfessionInfo();
    if(option == "Tak" || option == "TAK" || option == "tak") {
        int profession = CreateProfessionScreen();

    } else return;
}
