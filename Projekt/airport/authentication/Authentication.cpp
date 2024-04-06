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
    document.append(bsoncxx::builder::basic::kvp("profession", "brak"));
    document.append(bsoncxx::builder::basic::kvp("disabled", false)); // jako default wartość, może potwierdzić to potem w celu uzyskania zniżek
    document.append(bsoncxx::builder::basic::kvp("premiumCard", "brak"));

    auto paymentMethodDocument = bsoncxx::builder::basic::document{};
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("type", "blik"));
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cardNumber", bsoncxx::types::b_null{})); // null jako wartosci, bo do blika niepotrzebne
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cvv", bsoncxx::types::b_null{}));

    document.append(bsoncxx::builder::basic::kvp("paymentMethod", paymentMethodDocument));

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
        auto paymentMethodDocument = userView["paymentMethod"].get_document().value;
        auto email = (std::string) userView["email"].get_string().value;
        auto isDisabled = userView["disabled"].get_bool().value;
        auto premiumCard = (std::string) userView["premiumCard"].get_string().value;
        auto paymentMethod = paymentMethodDocument["type"].get_string().value;
        user.username = username;
        user.setPassword(password);
        user.email = email;
        user.isDisabled = isDisabled;
        user.profession = userView["profession"].get_string().value;
        user.premiumCard = premiumCard;
        user.paymentMethod = paymentMethod;
        promise.set_value(true); // Ustawienie wartości zwracanej na true
        validFunction("Zalogowano pomyślnie.", "Witamy w systemie.");
    } else {
        errorFunction("Wprowadzono niepoprawne dane bądź taki użytkownik nie istnieje.", "");
        promise.set_value(false); // Ustawienie wartości zwracanej na false
    }
}
