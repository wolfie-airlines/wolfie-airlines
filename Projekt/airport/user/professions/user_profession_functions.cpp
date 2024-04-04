#include "user_profession_functions.h"
#include "prints/profession_prints.h"

void handleProfession(User& user) {
    std::string option = displayProfessionInfo();
    std::cout << option;
    if(option == "Tak" || option == "TAK" || option == "tak") {
        int profession = CreateProfessionScreen();
    } else return;
}
