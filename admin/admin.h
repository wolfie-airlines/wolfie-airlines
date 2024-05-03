/**
 * @file admin.h
 * @brief This file contains the declaration of the Admin class.
 */

#ifndef AIRPORT_ADMIN_H
#define AIRPORT_ADMIN_H

#include "../user/user.h"

/**
 * @class Admin
 * @brief This class represents an admin user.
 * @details It inherits from the User class and adds additional functionality specific to admins.
 */
class Admin : public User {
 public:
  /**
   * @brief Constructs a new Admin object.
   * @param username The username of the admin.
   * @param email The email of the admin.
   * @param discount The discount available to the admin.
   * @param discount_type The type of discount available to the admin.
   * @param premium_card The premium card of the admin.
   * @param payment_method The payment method of the admin.
   * @param client The MongoDB client.
   * @param profession The profession of the admin.
   * @param registration_date The registration date of the admin.
   * @param money_spent The amount of money spent by the admin.
   * @param money_saved The amount of money saved by the admin.
   * @param ticket_bought The number of tickets bought by the admin.
   * @param user_flights The flights of the admin.
   * @param is_admin A flag indicating whether the user is an admin.
   * @param hashed_admin_password The hashed password of the admin.
   */
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

  /**
   * @brief Constructs a new Admin object from a User object.
   * @param user The User object.
   */
  Admin(const User &user)
      : User(user), hashed_admin_password_("") {}

  std::string hashed_admin_password_; ///< The hashed password of the admin.

  /**
   * @brief Adds a flight.
   * @param user The user to add the flight to.
   */
  void AddFlight(User &user);

  /**
   * @brief Adds a verification question.
   * @param user The user to add the verification question to.
   */
  void AddVerificationQuestion(User &user);

  /**
   * @brief Manages users.
   * @param user The user to manage.
   */
  void ManageUsers(User &user);

  /**
   * @brief Adds a luggage item.
   * @param user The user to add the luggage item to.
   */
  void AddLuggageItem(User &user);
};

#endif  // AIRPORT_ADMIN_H