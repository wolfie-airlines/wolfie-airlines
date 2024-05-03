#include "user_profession_functions.h"

#include "../../functions/info_prints/info_prints.h"
#include "profession_choice.h"
#include "profession_prints/profession_prints.h"

void HandleProfessionChoice(int choice, User &user) {
  if (choice == 0) {
    MusicProfession(user);
  } else if (choice == 1) {
    DoctorProfession(user);
  } else if (choice == 2) {
    MathProfession(user);
  } else if (choice == 3) {
    InformaticProfession(user);
  } else if (choice == 4) {
    PoliceProfession(user);
  } else {
    return;
  }
}

void HandleProfession(User &user) {
  std::string option = DisplayProfessionInfo();
  if (option == "Tak" || option == "TAK" || option == "tak") {
    int profession = CreateProfessionScreen();
    HandleProfessionChoice(profession, user);
  } else
    return;
}
