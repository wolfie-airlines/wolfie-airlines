#include "premium_cards.h"
#include "premium_cards_prints/premium_cards_prints.h"
#include "../../functions/info_print_functions.h"

double getCardDiscount(const std::string& card) {
    if(card == "szara") {
        return 1;
    } else if(card == "niebieska") {
        return 0.95;
    } else if(card == "złota") {
        return 0.95;
    } else if(card == "platynowa") {
        return 0.85;
    } else {
        return 1;
    }
}

std::string recognizeDiscountCard(double discount) {
    if(discount == 1) {
        return "szara";
    } else if(discount == 0.95) {
        return "niebieska";
    } else if(discount == 0.9) {
        return "złota";
    } else if(discount == 0.85) {
        return "platynowa";
    } else {
        return "brak";
    }
}

void handleCardChoice(const std::string& card, int price, User& user) {
    bool valid = validCardPayment(user, price);
    if(valid) {
        user.setPremiumCard(user, card);
    } else {
        return;
    }
}

void handlePremiumCard(User& user) {
    std::string choice = displayPremiumCardInfo();
    std::string card;
    int price;
    std::string premiumCard = recognizeDiscountCard(user.discount);

    for(int i = 0; i < choice.size(); i++) {
        choice[i] = tolower(choice[i]);
    }

    for(int i = 0; i < premiumCard.size(); i++) {
        premiumCard[i] = tolower(premiumCard[i]);
    }

    if(choice == premiumCard) {
        errorFunction("Posiadasz już tę kartę premium.", "");
        return;
    }

    if(choice == "szara") {
        card = "szara";
        price = 100;
    } else if(choice == "niebieska") {
        card = "niebieska";
        price = 200;
    } else if(choice == "złota") {
        card = "złota";
        price = 350;
    } else if(choice == "platynowa") {
        card = "platynowa";
        price = 450;
    } else {
        return;
    }
    handleCardChoice(card,price, user);
}