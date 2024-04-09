#include "premium_cards.h"
#include "premium_cards_prints/premium_cards_prints.h"
#include "../../functions/info_print_functions.h"

void User::setPremiumCard(User& user, const std::string& card) {
    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", user.email),
            bsoncxx::builder::basic::kvp("password", user.getPassword())
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

    mongocxx::cursor cursor_user = user.getCollection().find(filter_view_email_password);

    if (cursor_user.begin() == cursor_user.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("premiumCard", card)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    user.getCollection().update_one(filter_view_email_password, update_view);

    user.premiumCard = card;
    validFunction("Karta została przypisana do konta", "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
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