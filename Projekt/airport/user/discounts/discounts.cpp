#include "discounts.h"

#include "../../functions/info_prints/info_prints.h"
#include "discounts_prints/discounts_prints.h"

double getDiscount(std::string choice) {
  if (choice == "1") {
    // weteran
    return 0.05;
  } else if (choice == "2") {
    // karta inwalidzka
    return 0.4;
  } else if (choice == "3") {
    // emeryt
    return 0.45;
  } else if (choice == "4") {
    // student
    return 0.49;
  } else {
    return 1;
  }
}

void handleDiscountChoice(User &user, std::string choice) {
  bool valid = ValidDiscount(choice);
  if (valid) {
    user.SetDiscount(getDiscount(choice), "ulga");
  } else {
    PrintErrorMessage("Nie udało się przypisać zniżki do konta.", "");
    return;
  }
}

void PrintDiscountCard(User &user) {
  std::string choice = DisplayDiscountInfo();
  if (choice == "back") {
    return;
  }
  handleDiscountChoice(user, choice);
}