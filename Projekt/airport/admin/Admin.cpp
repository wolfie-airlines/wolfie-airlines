#include "Admin.h"

#include <utility>

Admin::Admin(const std::string& username, const std::string& email, double discount, const std::string& discountType, const std::string& premiumCard,
             const std::string& paymentMethod, mongocxx::client& client, const std::string& profession,
             const std::string& registrationDate, double moneySpent, double moneySaved, int ticketBought,
             const std::vector<bsoncxx::document::value>& userFlights, bool isAdmin, std::string hashedAdminPassword)
        : User(username, email, discount, discountType, premiumCard, paymentMethod, client, profession, registrationDate, moneySpent, moneySaved, ticketBought, userFlights, isAdmin), hashedAdminPassword(std::move(hashedAdminPassword)) {}

// Implementacje metod specyficznych dla administratora

void Admin::addFlight() {
    // Implementacja metody dodawania lotów
}

void Admin::addVerificationQuestion() {
    // Implementacja metody dodawania pytań dla weryfikacji zawodu użytkownika
}

void Admin::manageUsers() {
    // Implementacja metody zarządzania wszystkimi użytkownikami
}