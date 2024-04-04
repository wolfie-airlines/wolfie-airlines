#include "User.h"
#include "../functions/info_print_functions.h"

#include <utility>

User::User(std::string username, std::string email, bool isDisabled, std::string premiumCard, std::string password,
           std::string paymentMethod, mongocxx::client &client)
        : username(std::move(username)), email(std::move(email)), password(std::move(password)), isDisabled(isDisabled), premiumCard(std::move(premiumCard)), paymentMethod(std::move(paymentMethod)),
          _client(client) {}


User User::getUser() {
    return User{_client};
}

void User::setIsDisabled(bool isDis) {
    isDisabled = isDis;
}

void User::setPremiumCard(const std::string &card) {
    premiumCard = card;
}

void User::setPaymentMethod(const std::string &payment) {
    paymentMethod = payment;
}

void User::changeUsername(const std::string &newUsername) {
    // sprawdzenie czy nazwa jest zajeta
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("username", newUsername)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() != cursor.end()) {
        errorFunction("Nazwa użytkownika jest już zajęta.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("username", newUsername)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    username = newUsername;
    validFunction("Nazwa użytkownika została pomyślnie zmieniona.", "");
}

void User::changeEmail(const std::string &newEmail) {
    //sprawdzanie czy email jest zajety
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", newEmail)
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = _collection.find(filter_view);
    if (cursor.begin() != cursor.end()) {
        errorFunction("Ten adres e-mail jest już zajęty.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("email", newEmail)
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    email = newEmail;
    validFunction("Adres e-mail został pomyślnie zmieniony.", "");
}


