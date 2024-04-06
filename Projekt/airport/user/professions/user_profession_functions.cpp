#include "user_profession_functions.h"
#include "prints/profession_prints_n_handler.h"
#include "profession_choice.h"
#include "../../functions/info_print_functions.h"

void handleProfessionChoice(int choice, User& user) {
    if(choice==0) {
        musicProfession(user);
    } else if(choice == 1) {
        doctorProfession(user);
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
        //check if user has already chosen a profession
        if(user.profession != "brak") {
            errorFunction("Przecież już masz swój zawód!", "Pracujesz jako " + user.profession + ".");
            return;
        }
        int profession = CreateProfessionScreen();
        handleProfessionChoice(profession, user);
    } else return;
}
