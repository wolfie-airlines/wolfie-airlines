#include "admin.h"

#include <utility>

Admin::Admin(const std::string &username,
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
             std::string hashed_admin_password)
    : User(username,
           email,
           discount,
           discount_type,
           premium_card,
           payment_method,
           client,
           profession,
           registration_date,
           money_spent,
           money_saved,
           ticket_bought,
           user_flights,
           is_admin), hashed_admin_password_(std::move(hashed_admin_password)) {}

void Admin::AddFlight() {
  // TODO
}

void Admin::AddVerificationQuestion() {
  // TODO
}

void Admin::ManageUsers() {
  // TODO
}