#include "user_profession_functions.h"
#include "prints/profession_prints.h"
#include "profession_choice.h"

void handleProfessionChoice(int choice) {
    if(choice==0) {
        musicProfession();
    } else if(choice == 1) {
        // Lekarz
    } else if(choice == 2) {
        //Sportowiec
        // Dodatkowe menu dla wyboru dyscypliny
    } else if (choice==3) {
        // Matematyk
    } else if (choice == 4) {
        // Informatyk
    } else {
        return;
    }
}

void handleProfession(User& user) {
    std::string option = displayProfessionInfo();
    if(option == "Tak" || option == "TAK" || option == "tak") {
        int profession = CreateProfessionScreen();
        handleProfessionChoice(profession);
    } else return;
}
