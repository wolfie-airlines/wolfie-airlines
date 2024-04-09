#include "premium_cards.h"
#include "premium_cards_prints/premium_cards_prints.h"

void handleCardChoice(const std::string& card, int price, User& user) {
    // ekran płatności za kartę
    cardPaymentScreen(user, price);
    // jeśli płatność użytkownika przejdzie pomyślnie ustaw kartę

    // jeśli płatność użytkownika nie przejdzie zwróć błąd
}

void handlePremiumCard(User& user) {
    std::string choice = displayPremiumCardInfo();
    std::string card;
    int price;
    // Jeśli użytkownik wpisał Szara lub szara lub SZARA
    if(choice == "Szara" || choice == "szara" || choice == "SZARA") {
        card = "szara";
        price = 100;
    } else if(choice == "Niebieska" || choice == "niebieska" || choice == "NIEBIESKA") {
        card = "niebieska";
        price = 200;
    } else if(choice == "Złota" || choice == "złota" || choice == "ZŁOTA") {
        card = "złota";
        price = 350;
    } else if(choice == "Platynowa" || choice == "platynowa" || choice == "PLATYNOWA") {
        card = "platynowa";
        price = 450;
    } else {
        return;
    }
    handleCardChoice(card,price, user);
}