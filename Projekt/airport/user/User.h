#ifndef USER_H
#define USER_H

#include <string>

#include "../flights/FlightConnection.h"
#include "../luggage/Luggage.h"
#include "mongocxx/client.hpp"

class User {
 private:
  mongocxx::database _db;
  mongocxx::collection _collection;
  std::string password;

 protected:
  mongocxx::client &_client;

 public:
  explicit User(mongocxx::client &client)
      : _client(client),
        _db(client["projekt"]),
        _collection(_db["users"]),
        username("gosc"),
        email("brak"),
        discount(1.0),
        discountType("brak"),
        premiumCard("brak"),
        paymentMethod("blik"),
        profession("brak"),
        registrationDate("brak"),
        moneySpent(0),
        moneySaved(0),
        ticketBought(0),
        userFlights(std::vector<bsoncxx::document::value>{}),
        isAdmin(false) {}
  User(std::string username, std::string email, double discount,
       std::string discountType, std::string premiumCard,
       std::string paymentMethod, mongocxx::client &client,
       std::string profession, std::string registrationDate,
       double moneySpent, double moneySaved,
       int ticketBought, std::vector<bsoncxx::document::value> userFlights, bool isAdmin);

  // Obiekt użytkownika (dane)
  std::string username;
  std::string profession;
  std::string email;
  std::string discountType;
  double discount;
  std::string premiumCard;
  std::string paymentMethod;
  std::string registrationDate;
  double moneySpent;
  double moneySaved;
  int ticketBought;
  std::vector<bsoncxx::document::value> userFlights;
  bool isAdmin;

  // Funkcje użytkownika (metody)
  void reset();
  mongocxx::collection &getCollection();
  mongocxx::collection getSpecificCollection(const std::string &collectionName);
  std::string getPassword();
  void setPassword(const std::string &password);
  void setPremiumCard(User &user, const std::string &card);
  void setBlik(const std::string &paymentMethod);
  void setVisa(const std::string &cNumber, const std::string &cCVV);
  void changeUsername(const std::string &username);
  void changeEmail(const std::string &email);
  void changePassword(const std::string &password);
  void setDiscount(double discount, const std::string &discountType);
  [[nodiscard]] double getDiscount() const;
  [[nodiscard]] std::string recognizeDiscount() const;
  void addTicketToUser(const std::vector<int> &seats, const FlightConnection &flightConnection);
  void updateMoneySaved(double normalPrice, double discountPrice);
  void loginAsAdmin();
  [[nodiscard]] bool checkIfAdmin() const;
  void setIsAdmin(bool isAdministrator) { User::isAdmin = isAdministrator; }
  void luggageCheckin(int flightNumber);
  mongocxx::cursor findUserInDatabase();

  template<typename T>
  void updateUserInDatabase(
      const std::string &valueInDatabase,
      const T &valueToSet) {
    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp(valueInDatabase, valueToSet))));

    bsoncxx::document::view update_view = update_builder.view();
    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("email", email),
        bsoncxx::builder::basic::kvp("password", getPassword()));

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    _collection.update_one(filter_view_email_password, update_view);
  }
};

#endif  // USER_H
