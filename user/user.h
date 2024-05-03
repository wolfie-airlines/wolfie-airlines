#ifndef USER_H
#define USER_H

#include <string>

#include "../flights/flight_connection.h"
#include "../luggage/luggage.h"
#include "mongocxx/client.hpp"

class Admin;

class User {
 private:
  mongocxx::database _db_;
  mongocxx::collection _collection_;
  std::string _password_;

 protected:
  mongocxx::client &_client;

 public:
  explicit User(mongocxx::client &client)
      : _client(client),
        _db_(client["projekt"]),
        _collection_(_db_["users"]),
        username_("gosc"),
        email_("brak"),
        discount_(1.0),
        discount_type_("brak"),
        premium_card_("brak"),
        payment_method_("blik"),
        profession_("brak"),
        registration_date_("brak"),
        money_spent_(0),
        money_saved_(0),
        ticket_bought_(0),
        user_flights_(std::vector<bsoncxx::document::value>{}),
        is_admin_(false) {}
  User(std::string username, std::string email, double discount,
       std::string discount_type, std::string premium_card,
       std::string payment_method, mongocxx::client &client,
       std::string profession, std::string registration_date,
       double money_spent, double money_saved,
       int ticket_bought, std::vector<bsoncxx::document::value> user_flights, bool is_admin);

  // Obiekt użytkownika (dane)
  std::string username_;
  std::string profession_;
  std::string email_;
  std::string discount_type_;
  double discount_;
  std::string premium_card_;
  std::string payment_method_;
  std::string registration_date_;
  double money_spent_;
  double money_saved_;
  int ticket_bought_;
  std::vector<bsoncxx::document::value> user_flights_;
  bool is_admin_;

  // Funkcje użytkownika (metody)
  void Reset();
  mongocxx::collection &GetCollection();
  mongocxx::collection GetSpecificCollection(const std::string &collection_name);
  std::string GetPassword();
  void SetPassword(const std::string &password);
  void SetPremiumCard(User &user, const std::string &card);
  void SetBlik(const std::string &payment_method);
  void SetVisa(const std::string &card_number, const std::string &card_cvv);
  void ChangeUsername(const std::string &username);
  void ChangeEmail(const std::string &email);
  void ChangePassword(const std::string &password);
  void SetDiscount(double discount, const std::string &discount_type);
  [[nodiscard]] double GetDiscount() const;
  [[nodiscard]] std::string RecognizeDiscount() const;
  void AddTicketToUser(const std::vector<int> &seats, const FlightConnection &flight_connection);
  void UpdateMoneySaved(double normal_price, double discount_price);
  Admin *LoginAsAdmin();
  [[nodiscard]] bool CheckIfAdmin() const;
  void setIsAdmin(bool is_administrator) { User::is_admin_ = is_administrator; }
  void LuggageCheckin(int flight_number);
  mongocxx::cursor FindUserInDatabase();

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
