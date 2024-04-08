#include "user_profession_functions.h"
#include "prints/profession_prints.h"
#include "profession_choice.h"
#include "../../functions/info_print_functions.h"

void handleProfessionChoice(int choice, User& user) {
    if(choice==0) {
        musicProfession(user);
    } else if(choice == 1) {
        doctorProfession(user);
    } else if(choice == 2) {
        mathProfession(user);
    } else if (choice == 3) {
        informaticProfession(user);
    } else {
        return;
    }
}

void handleProfession(User& user) {
    std::string option = displayProfessionInfo();
    if(option == "Tak" || option == "TAK" || option == "tak") {
        int profession = CreateProfessionScreen();
        handleProfessionChoice(profession, user);
    } else return;
}
