#include "premium_cards.h"

#include "../../functions/info_prints/info_prints.h"
#include "premium_cards_prints/premium_cards_prints.h"

double GetCardDiscount(const std::string &card) {
  if (card == "szara") {
    return 1;
  } else if (card == "niebieska") {
    return 0.95;
  } else if (card == "złota") {
    return 0.95;
  } else if (card == "platynowa") {
    return 0.85;
  } else {
    return 1;
  }
}

std::string RecognizeDiscountCard(double discount) {
  if (discount == 1) {
    return "szara";
  } else if (discount == 0.95) {
    return "niebieska";
  } else if (discount == 0.9) {
    return "złota";
  } else if (discount == 0.85) {
    return "platynowa";
  } else {
    return "brak";
  }
}

void HandleCardChoice(const std::string &card, int price, User &user) {
  bool valid = ValidCardPayment(user, price);
  if (valid) {
    user.SetPremiumCard(user, card);
  } else {
    return;
  }
}

void HandlePremiumCard(User &user) {
  std::string choice = DisplayPremiumCardInfo();
  std::string card;
  int price;
  std::string premium_card = RecognizeDiscountCard(user.discount_);

  for (int i = 0; i < choice.size(); i++) {
    choice[i] = tolower(choice[i]);
  }

  for (int i = 0; i < premium_card.size(); i++) {
    premium_card[i] = tolower(premium_card[i]);
  }

  if (choice == premium_card) {
    PrintErrorMessage("Posiadasz już tę kartę premium.", "");
    return;
  }

  if (choice == "szara") {
    card = "szara";
    price = 100;
  } else if (choice == "niebieska") {
    card = "niebieska";
    price = 200;
  } else if (choice == "złota") {
    card = "złota";
    price = 350;
  } else if (choice == "platynowa") {
    card = "platynowa";
    price = 450;
  } else {
    return;
  }
  HandleCardChoice(card, price, user);
}