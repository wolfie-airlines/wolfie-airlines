#ifndef AIRPORT_ADMIN_H
#define AIRPORT_ADMIN_H

#include "../user/user.h"

class Admin : public User {
 public:
  Admin(const std::string &username,
        const std::string &email,
        double discount,
        const std::string &discount_type,
        const std::string &premium_card,
        const std::string &payment_method,
        mongocxx::client &client,
        const std::string &profession,
        const std::string &registration_date,
        double money_spent,
        double money_saved,
        int ticket_bought,
        const std::vector<bsoncxx::document::value> &user_flights,
        bool is_admin,
        std::string hashed_admin_password);

  std::string hashed_admin_password_;  // Haszowane hasło administratora
  // Metody dla admina
  void AddFlight();                // Dodawanie lotów
  void AddVerificationQuestion();  // Dodawanie pytań dla weryfikacji zawodu użytkownika
  void ManageUsers();              // Zarządzanie wszystkimi użytkownikami
};

#endif  // AIRPORT_ADMIN_H
