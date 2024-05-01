#ifndef AIRPORT_ADMIN_H
#define AIRPORT_ADMIN_H

#include "../user/User.h"

class Admin : public User {
 public:
  Admin(const std::string &username,
        const std::string &email,
        double discount,
        const std::string &discountType,
        const std::string &premiumCard,
        const std::string &paymentMethod,
        mongocxx::client &client,
        const std::string &profession,
        const std::string &registrationDate,
        double moneySpent,
        double moneySaved,
        int ticketBought,
        const std::vector<bsoncxx::document::value> &userFlights,
        bool isAdmin,
        std::string hashedAdminPassword);

  std::string hashedAdminPassword;  // Haszowane hasło administratora
  // Metody dla admina
  void addFlight();                // Dodawanie lotów
  void addVerificationQuestion();  // Dodawanie pytań dla weryfikacji zawodu użytkownika
  void manageUsers();              // Zarządzanie wszystkimi użytkownikami
};

#endif  // AIRPORT_ADMIN_H
