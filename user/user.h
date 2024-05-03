/**
 * @file user.h
 * @brief Ten plik zawiera deklarację klasy User.
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
 * @brief Reprezentuje użytkownika w systemie.
 */
class User {
 private:
  mongocxx::database _db_; ///< Obiekt bazy danych.
  mongocxx::collection _collection_; ///< Obiekt kolekcji.
  std::string _password_; ///< Hasło użytkownika.

 protected:
  mongocxx::client &_client; ///< Klient MongoDB.

 public:
  /**
   * @brief Konstruuje nowy obiekt User.
   * @param client Klient MongoDB.
   */
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

  /**
   * @brief Konstruuje nowy obiekt User z określonymi parametrami.
   */
  User(std::string username, std::string email, double discount,
       std::string discount_type, std::string premium_card,
       std::string payment_method, mongocxx::client &client,
       std::string profession, std::string registration_date,
       double money_spent, double money_saved,
       int ticket_bought, std::vector<bsoncxx::document::value> user_flights, bool is_admin);

  // Obiekt użytkownika (dane)
  std::string username_; ///< Nazwa użytkownika.
  std::string profession_; ///< Zawód użytkownika.
  std::string email_; ///< Email użytkownika.
  std::string discount_type_; ///< Typ zniżki użytkownika.
  double discount_; ///< Wartość zniżki użytkownika.
  std::string premium_card_; ///< Karta premium użytkownika.
  std::string payment_method_; ///< Metoda płatności użytkownika.
  std::string registration_date_; ///< Data rejestracji użytkownika.
  double money_spent_; ///< Całkowita kwota wydana przez użytkownika.
  double money_saved_; ///< Całkowita kwota zaoszczędzona przez użytkownika.
  int ticket_bought_; ///< Całkowita liczba biletów kupionych przez użytkownika.
  std::vector<bsoncxx::document::value> user_flights_; ///< Loty użytkownika.
  bool is_admin_; ///< Czy użytkownik jest administratorem.

  // Funkcje użytkownika (metody)
  void Reset(); ///< Resetuje użytkownika.
  mongocxx::collection &GetCollection(); ///< Zwraca kolekcję.
  mongocxx::collection GetSpecificCollection(const std::string &collection_name); ///< Zwraca określoną kolekcję.
  std::string GetPassword(); ///< Zwraca hasło.
  void SetPassword(const std::string &password); ///< Ustawia hasło.
  void SetPremiumCard(User &user, const std::string &card); ///< Ustawia kartę premium.
  void SetBlik(const std::string &payment_method); ///< Ustawia metodę płatności Blik.
  void SetVisa(const std::string &card_number, const std::string &card_cvv); ///< Ustawia metodę płatności Visa.
  void ChangeUsername(const std::string &username); ///< Zmienia nazwę użytkownika.
  void ChangeEmail(const std::string &email); ///< Zmienia email.
  void ChangePassword(const std::string &password); ///< Zmienia hasło.
  void SetDiscount(double discount, const std::string &discount_type); ///< Ustawia zniżkę.
  [[nodiscard]] double GetDiscount() const; ///< Zwraca zniżkę.
  [[nodiscard]] std::string RecognizeDiscount() const; ///< Rozpoznaje zniżkę.
  void AddTicketToUser(const std::vector<int> &seats,
                       const FlightConnection &flight_connection); ///< Dodaje bilet do użytkownika.
  void UpdateMoneySaved(double normal_price, double discount_price); ///< Aktualizuje zaoszczędzone pieniądze.
  Admin *LoginAsAdmin(); ///< Loguje jako admin.
  [[nodiscard]] bool CheckIfAdmin() const; ///< Sprawdza, czy użytkownik jest administratorem.
  void SetIsAdmin(bool is_administrator) { User::is_admin_ = is_administrator; } ///< Ustawia, czy użytkownik jest administratorem.
  void LuggageCheckin(int flight_number); ///< Odprawia bagaż.
  mongocxx::cursor FindUserInDatabase(); ///< Znajduje użytkownika w bazie danych.

  /**
   * @brief Aktualizuje użytkownika w bazie danych.
   * @tparam T Typ wartości do ustawienia.
   * @param value_in_database Wartość w bazie danych.
   * @param value_to_set Wartość do ustawienia.
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
