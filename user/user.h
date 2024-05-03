/**
 * @file user.h
 * @brief This file contains the declaration of the User class.
 */

#ifndef USER_H
#define USER_H

#include <string>

#include "../flights/flight_connection.h"
#include "../luggage/luggage.h"
#include "mongocxx/client.hpp"

class Admin;

/**
 * @class User
 * @brief Represents a user in the system.
 */
class User {
 private:
  mongocxx::database _db_; ///< The database object.
  mongocxx::collection _collection_; ///< The collection object.
  std::string _password_; ///< The user's password.

 protected:
  mongocxx::client &_client; ///< The MongoDB client.

 public:
  /**
   * @brief Constructs a new User object.
   * @param client The MongoDB client.
   */
  explicit User(mongocxx::client &client);

  /**
   * @brief Constructs a new User object with specified parameters.
   */
  User(std::string username, std::string email, double discount,
       std::string discount_type, std::string premium_card,
       std::string payment_method, mongocxx::client &client,
       std::string profession, std::string registration_date,
       double money_spent, double money_saved,
       int ticket_bought, std::vector<bsoncxx::document::value> user_flights, bool is_admin);

  std::string username_; ///< The username of the user.
  std::string profession_; ///< The profession of the user.
  std::string email_; ///< The email of the user.
  std::string discount_type_; ///< The type of discount the user has.
  double discount_; ///< The discount rate of the user.
  std::string premium_card_; ///< The premium card of the user.
  std::string payment_method_; ///< The payment method of the user.
  std::string registration_date_; ///< The registration date of the user.
  double money_spent_; ///< The total money spent by the user.
  double money_saved_; ///< The total money saved by the user.
  int ticket_bought_; ///< The total tickets bought by the user.
  std::vector<bsoncxx::document::value> user_flights_; ///< The flights of the user.
  bool is_admin_; ///< Whether the user is an admin.

  void Reset(); ///< Resets the user.
  mongocxx::collection &GetCollection(); ///< Returns the collection.
  mongocxx::collection GetSpecificCollection(const std::string &collection_name); ///< Returns a specific collection.
  std::string GetPassword(); ///< Returns the password.
  void SetPassword(const std::string &password); ///< Sets the password.
  void SetPremiumCard(User &user, const std::string &card); ///< Sets the premium card.
  void SetBlik(const std::string &payment_method); ///< Sets the Blik payment method.
  void SetVisa(const std::string &card_number, const std::string &card_cvv); ///< Sets the Visa payment method.
  void ChangeUsername(const std::string &username); ///< Changes the username.
  void ChangeEmail(const std::string &email); ///< Changes the email.
  void ChangePassword(const std::string &password); ///< Changes the password.
  void SetDiscount(double discount, const std::string &discount_type); ///< Sets the discount.
  [[nodiscard]] double GetDiscount() const; ///< Returns the discount.
  [[nodiscard]] std::string RecognizeDiscount() const; ///< Recognizes the discount.
  void AddTicketToUser(const std::vector<int> &seats,
                       const FlightConnection &flight_connection); ///< Adds a ticket to the user.
  void UpdateMoneySaved(double normal_price, double discount_price); ///< Updates the money saved.
  Admin *LoginAsAdmin(); ///< Logs in as an admin.
  [[nodiscard]] bool CheckIfAdmin() const; ///< Checks if the user is an admin.
  void SetIsAdmin(bool is_administrator) { User::is_admin_ = is_administrator; } ///< Sets whether the user is an admin.
  void LuggageCheckin(int flight_number); ///< Checks in luggage.
  mongocxx::cursor FindUserInDatabase(); ///< Finds the user in the database.

  /**
   * @brief Updates the user in the database.
   * @tparam T The type of the value to set.
   * @param value_in_database The value in the database.
   * @param value_to_set The value to set.
   */
  template<typename T>
  void UpdateUserInDatabase(
      const std::string &value_in_database,
      const T &value_to_set) {
    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp(value_in_database, value_to_set))));

    bsoncxx::document::view update_view = update_builder.view();
    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("email_", email_),
        bsoncxx::builder::basic::kvp("password", GetPassword()));

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    _collection_.update_one(filter_view_email_password, update_view);
  }
};

#endif  // USER_H