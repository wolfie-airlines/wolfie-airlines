#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
// ^ żeby nie podkreślało mi linijek
#include "Authentication.h"
#include "../user/User.h"
#include "../functions/info_print_functions.h"
#include <future>

Authentication::Authentication(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
        : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

bool Authentication::registerUser(const std::string& username, const std::string& email, const std::string& password) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("email", email));
    document.append(bsoncxx::builder::basic::kvp("password", password));
    document.append(bsoncxx::builder::basic::kvp("disabled", false)); // musi to potwierdzić, ale dopiero potem
    document.append(bsoncxx::builder::basic::kvp("premiumCard", "brak"));
    document.append(bsoncxx::builder::basic::kvp("paymentMethod", "blik"));

    auto result = _collection.insert_one(document.view());
    return result ? true : false;
}

void Authentication::authenticateUser(const std::string& username, const std::string& password, std::promise<bool>&& promise, User& user) {
    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("password", password));

    auto result = _collection.find_one(document.view());
    if (result) {
        bsoncxx::document::view userView = result->view();
        auto email = (std::string) userView["email"].get_string().value;
        auto isDisabled = userView["disabled"].get_bool().value;
        auto premiumCard = (std::string) userView["premiumCard"].get_string().value;
        auto paymentMethod = (std::string) userView["paymentMethod"].get_string().value;
        user = User{username, email, isDisabled, premiumCard, paymentMethod};
        promise.set_value(true); // Ustawienie wartości zwracanej na true
        validFunction("Zalogowano pomyślnie.", "Witamy w systemie.");
    } else {
        errorFunction("Wprowadzono niepoprawne dane bądź taki użytkownik nie istnieje.", "");
        promise.set_value(false); // Ustawienie wartości zwracanej na false
    }
}

#pragma clang diagnostic pop