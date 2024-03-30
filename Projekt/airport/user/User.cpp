#include "User.h"

#include <utility>

User::User(std::string  username, std::string  email, bool isDisabled, std::string premiumCard, std::string paymentMethod)
        : username(std::move(username)), email(std::move(email)), isDisabled(isDisabled), premiumCard(std::move(premiumCard)), paymentMethod(std::move(paymentMethod))
{}

std::string User::getUsername() const { return username; }

std::string User::getEmail() const { return email; }

User User::getUser() {
    return {};
}

bool User::getIsDisabled() const {
    return isDisabled;
}

std::string User::getPremiumCard() const {
    return premiumCard;
}

std::string User::getPaymentMethod() const {
    return paymentMethod;
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

bool User::setUsername(const std::string &newUsername) {

    //sprawdzenie czy nazwa jest zajeta
    // jesli nie, ustawianie nowej

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("departureCity", departCity),
            bsoncxx::builder::basic::kvp("destinationCity", destinCity)
    );
    bsoncxx::document::view filter_view = filter_builder.view();

    mongocxx::cursor cursor = _collection.find(filter_view);
    for (auto&& doc : cursor) {
        bsoncxx::document::view view = doc;
        auto flightId = (std::string) view["identifier"].get_string().value;
        auto depCity = (std::string) view["departureCity"].get_string().value;
        auto destCity = (std::string) view["destinationCity"].get_string().value;
        auto depTime = (std::string) view["departureTime"].get_string().value;
        auto arrTime = (std::string) view["arrivalTime"].get_string().value;
        double flightPrice = view["price"].get_double().value;
        return FlightConnection{flightId, depCity, destCity, depTime, arrTime, flightPrice};
    }
    return FlightConnection{"", "", "", "", "", 0};
}
