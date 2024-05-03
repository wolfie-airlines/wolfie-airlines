/**
 * @file admin.h
 * @brief Ten plik zawiera deklarację klasy Admin.
 */

#ifndef AIRPORT_ADMIN_H
#define AIRPORT_ADMIN_H

#include "../user/user.h"

/**
 * @class Admin
 * @brief Ta klasa reprezentuje użytkownika admina.
 * @details Dziedziczy po klasie User i dodaje dodatkowe funkcje specyficzne dla adminów.
 */
class Admin : public User {
 public:
  /**
   * @brief Konstruuje nowy obiekt Admin.
   * @param username Nazwa użytkownika admina.
   * @param email Email admina.
   * @param discount Dostępna dla admina zniżka.
   * @param discount_type Typ dostępnej dla admina zniżki.
   * @param premium_card Karta premium admina.
   * @param payment_method Metoda płatności admina.
   * @param client Klient MongoDB.
   * @param profession Zawód admina.
   * @param registration_date Data rejestracji admina.
   * @param money_spent Kwota wydana przez admina.
   * @param money_saved Kwota zaoszczędzona przez admina.
   * @param ticket_bought Liczba biletów kupionych przez admina.
   * @param user_flights Loty admina.
   * @param is_admin Flaga wskazująca, czy użytkownik jest adminem.
   * @param hashed_admin_password Zaszyfrowane hasło admina.
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
   * @brief Konstruuje nowy obiekt Admin z obiektu User.
   * @param user Obiekt User.
   */
  Admin(const User &user)
      : User(user), hashed_admin_password_("") {}

  std::string hashed_admin_password_; ///< Zaszyfrowane hasło admina.

  /**
   * @brief Dodaje lot.
   * @param user Użytkownik, do którego dodawany jest lot.
   */
  void AddFlight(User &user);

  /**
   * @brief Dodaje pytanie weryfikacyjne.
   * @param user Użytkownik, do którego dodawane jest pytanie weryfikacyjne.
   */
  void AddVerificationQuestion(User &user);

  /**
   * @brief Zarządza użytkownikami.
   * @param user Użytkownik do zarządzania.
   */
  void ManageUsers(User &user);

  /**
   * @brief Dodaje przedmiot bagażu.
   * @param user Użytkownik, do którego dodawany jest przedmiot bagażu.
   */
  void AddLuggageItem(User &user);
};

#endif  // AIRPORT_ADMIN_H