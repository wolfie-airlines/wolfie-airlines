#include "Authentication.h"
#include "../user/User.h"
#include "../functions/info_print_functions.h"
#include <future>

Authentication::Authentication(const std::string& uri_str, const std::string& db_name, const std::string& collection_name)
        : _client{mongocxx::uri{uri_str}}, _db{_client[db_name]}, _collection{_db[collection_name]} {}

bool Authentication::registerUser(const std::string& username, const std::string& email, const std::string& password) {

    auto usernameAlreadyExists = _collection.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username)));
    if (usernameAlreadyExists) {
        errorFunction("Podana nazwa użytkownika jest już zajęta.", "Wybierz inną nazwę.");
        return false;
    }

    auto emailAlreadyExists = _collection.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("email", email)));
    if (emailAlreadyExists) {
        errorFunction("Podany adres e-mail jest już zajęty.", "Wybierz inny adres e-mail.");
        return false;
    }

    auto document = bsoncxx::builder::basic::document{};
    document.append(bsoncxx::builder::basic::kvp("username", username));
    document.append(bsoncxx::builder::basic::kvp("email", email));
    document.append(bsoncxx::builder::basic::kvp("password", password));
    document.append(bsoncxx::builder::basic::kvp("profession", "brak"));
    document.append(bsoncxx::builder::basic::kvp("premiumCard", "brak"));
    document.append(bsoncxx::builder::basic::kvp("moneySpent", 0.00));
    document.append(bsoncxx::builder::basic::kvp("ticketBought", 0));
    document.append(bsoncxx::builder::basic::kvp("discountType", "brak"));
    document.append(bsoncxx::builder::basic::kvp("discount", 1.00));


    // Pobieranie daty i godziny rejestracji - potrzebne do statystyk w profilu
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%H:%M %d.%m.%Y");
    std::string dateTime = ss.str();
    document.append(bsoncxx::builder::basic::kvp("registrationDate", dateTime));


    auto paymentMethodDocument = bsoncxx::builder::basic::document{};
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("type", "blik"));
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cardNumber", bsoncxx::types::b_null{})); // null jako wartosci, bo do blika niepotrzebne
    paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cvv", bsoncxx::types::b_null{}));

    document.append(bsoncxx::builder::basic::kvp("paymentMethod", paymentMethodDocument));

    auto userFlights = bsoncxx::builder::basic::array{};
    document.append(bsoncxx::builder::basic::kvp("userFlights", userFlights));

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
        auto userFlightsDocument = userView["userFlights"].get_array().value;
        auto email = (std::string) userView["email"].get_string().value;
        auto premiumCard = (std::string) userView["premiumCard"].get_string().value;
        auto paymentMethod = paymentMethodDocument["type"].get_string().value;
        auto moneySpent = userView["moneySpent"].get_double().value;
        auto ticketBought = userView["ticketBought"].get_int32().value;
        auto registrationDate = (std::string) userView["registrationDate"].get_string().value;
        auto discountType = (std::string) userView["discountType"].get_string().value;
        auto discount = userView["discount"].get_double().value;
        user.username = username;
        user.setPassword(password);
        user.discount = discount;
        user.email = email;
        user.discountType = discountType;
        user.profession = (std::string) userView["profession"].get_string().value;
        user.premiumCard = premiumCard;
        user.paymentMethod = paymentMethod;
        user.moneySpent = moneySpent;
        user.ticketBought = ticketBought;
        user.registrationDate = registrationDate;
        user.userFlights = userFlightsDocument;

        promise.set_value(true); // Ustawienie wartości zwracanej na true
        validFunction("Zalogowano pomyślnie.", "Witamy w systemie.");
    } else {
        errorFunction("Wprowadzono niepoprawne dane bądź taki użytkownik nie istnieje.", "");
        promise.set_value(false); // Ustawienie wartości zwracanej na false
    }
}
