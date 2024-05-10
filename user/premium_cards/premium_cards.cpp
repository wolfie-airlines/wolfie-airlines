#include "premium_cards.h"

#include "../../functions/info_prints/info_prints.h"
#include "premium_cards_prints/premium_cards_prints.h"

double GetCardDiscount(const std::string &card) {
    if (card == "grey") {
        return 1;
    } else if (card == "blue") {
        return 0.95;
    } else if (card == "gold") {
        return 0.95;
    } else if (card == "platinum") {
        return 0.85;
    } else {
        return 1;
    }
}

std::string RecognizeDiscountCard(double discount) {
    if (discount == 1) {
        return "grey";
    } else if (discount == 0.95) {
        return "blue";
    } else if (discount == 0.9) {
        return "gold";
    } else if (discount == 0.85) {
        return "platinum";
    } else {
        return "none";
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
        PrintErrorMessage("You already own this premium card.", "");
        return;
    }

    if (choice == "grey") {
        card = "grey";
        price = 100;
    } else if (choice == "blue") {
        card = "blue";
        price = 200;
    } else if (choice == "gold") {
        card = "gold";
        price = 350;
    } else if (choice == "platinum") {
        card = "platinum";
        price = 450;
    } else {
        return;
    }
    HandleCardChoice(card, price, user);
}