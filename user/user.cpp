#include "user.h"

#include <utility>

#include "../admin/admin.h"
#include "../env/env.h"
#include "../functions/helpers.h"
#include "../functions/info_prints/info_prints.h"
#include "bsoncxx/json.hpp"
#include "premium_cards/premium_cards.h"
#include "../functions/main_prints/main_prints.h"

User::User(std::string username,
           std::string email,
           double discount,
           std::string discount_type,
           std::string premium_card,
           std::string payment_method,
           mongocxx::client &client,
           std::string profession,
           std::string registration_date,
           double money_spent,
           double money_saved,
           int ticket_bought,
           std::vector<bsoncxx::document::value> user_flights,
           bool is_admin)
    : username_(std::move(username)),
      email_(std::move(email)),
      discount_(discount),
      discount_type_(std::move(discount_type)),
      premium_card_(std::move(premium_card)),
      payment_method_(std::move(payment_method)),
      _client(client),
      profession_(std::move(profession)),
      registration_date_(std::move(registration_date)),
      money_spent_(money_spent),
      money_saved_(money_saved),
      ticket_bought_(ticket_bought),
      user_flights_(std::move(user_flights)),
      is_admin_(is_admin) {}

// Resetowanie użytkownika
void User::Reset() {
  username_ = "gosc";
  email_ = "brak";
  discount_ = 1.0;
  discount_type_ = "brak";
  premium_card_ = "brak";
  payment_method_ = "blik";
  profession_ = "brak";
  registration_date_ = "brak";
  money_spent_ = 0;
  money_saved_ = 0;
  ticket_bought_ = 0;
  user_flights_.clear();
  is_admin_ = false;
}

mongocxx::collection &User::GetCollection() {
  return _collection_;
}

mongocxx::collection User::GetSpecificCollection(const std::string &collection_name) {
  return _db_[collection_name];
}

mongocxx::cursor User::FindUserInDatabase() {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();

  mongocxx::cursor cursor = _collection_.find(filter_view);
  return cursor;
}

// Ustawienia
std::string User::GetPassword() {
  std::string hashed_password = HashString(_password_);
  return hashed_password;
}

void User::SetPassword(const std::string &password) {
  User::_password_ = password;
}

void User::ChangePassword(const std::string &password) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection_.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  std::string repeated_password =
      DisplayMessageAndCaptureStringInput("Zmiana hasła", "Podaj ponownie nowe hasło żeby potwierdzić zmianę:");
  if (password != repeated_password) {
    PrintErrorMessage("Podane hasła nie są takie same.", "Spróbuj ponownie.");
    return;
  }

  std::string old_password =
      DisplayMessageAndCaptureStringInput("Zmiana hasła", "Podaj stare hasło żebyśmy mieli 200% pewności że to ty:");
  if (old_password != _password_) {
    PrintErrorMessage("Podane hasło nie jest poprawne.", "Spróbuj ponownie.");
    return;
  }

  std::string hashed_password = HashString(password);

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("password", hashed_password))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view_email_password, update_view);

  _password_ = hashed_password;
  PrintSuccessMessage("Hasło zostało pomyślnie zmienione.", "");
}

void User::ChangeUsername(const std::string &username) {
  // sprawdzenie, czy nazwa jest zajeta
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("username", username));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  if (cursor.begin() != cursor.end()) {
    PrintErrorMessage("Nazwa użytkownika jest już zajęta.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection_.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("username", username))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view_email_password, update_view);

  username_ = username;
  PrintSuccessMessage("Nazwa użytkownika została pomyślnie zmieniona.", "");
}

void User::ChangeEmail(const std::string &email) {
  // sprawdzanie, czy email jest zajety
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  if (cursor.begin() != cursor.end()) {
    PrintErrorMessage("Ten adres e-mail jest już zajęty.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection_.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("email", email))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view_email_password, update_view);

  email_ = email;
  PrintSuccessMessage("Adres e-mail został pomyślnie zmieniony.", "");
}

bool User::CheckIfAdmin() const {
  return is_admin_;
}

Admin *User::LoginAsAdmin() {
  if (is_admin_) {
    Admin *admin = new Admin(*this);
    return admin;
  }
  EnvParser envParser;
  envParser.ParseEnvFile();
  std::string admin_password = envParser.GetValue("ADMIN_PASSWORD");
  std::string admin_password_hashed = HashString(admin_password);

  std::string
      password = DisplayMessageAndCaptureStringInput("Logowanie jako administrator", "Podaj hasło administratora: ");
  std::string password_hashed = HashString(password);

  if (password_hashed == admin_password_hashed) {
    PrintSuccessMessage("Zalogowano jako administrator.",
                        "Witamy Cię serdecznie. Korzystaj ze swojej władzy rozważnie.");
    Admin *admin = new Admin(username_,
                             email_,
                             discount_,
                             discount_type_,
                             premium_card_,
                             payment_method_,
                             _client,
                             profession_,
                             registration_date_,
                             money_spent_,
                             money_saved_,
                             ticket_bought_,
                             user_flights_,
                             true,
                             admin_password_hashed);
    SetIsAdmin(true);
    return admin;
  } else {
    PrintErrorMessage("Logowanie nie powiodło się.", "Wprowadzono błędne hasło administratora.");
    return nullptr;
  }
}

// Płatności użytkownika (zniżki, ulgi, płatności kartą/blikiem)

double User::GetDiscount() const {
  return discount_;
}

std::string User::RecognizeDiscount() const {
  double discount = GetDiscount();
  if (discount == 0.05) {
    return "Weteran wojenny";
  } else if (discount == 0.4) {
    return "Osoba niepełnosprawna";
  } else if (discount == 0.45) {
    return "Emeryt";
  } else if (discount == 0.49) {
    return "Student";
  } else {
    return "brak";
  }
}

void User::SetDiscount(double discount, const std::string &discount_type) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

  mongocxx::cursor cursor_user = FindUserInDatabase();

  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("discountType", discount_type),
          bsoncxx::builder::basic::kvp("discount", discount))));

  bsoncxx::document::view update_view = update_builder.view();
  GetCollection().update_one(filter_view_email_password, update_view);
  User::discount_ = discount;
  User::discount_type_ = discount_type;
  PrintSuccessMessage("Zniżka została przypisana do konta",
                      "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
}

void User::SetPremiumCard(User &user, const std::string &card) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", user.email_),
      bsoncxx::builder::basic::kvp("password", user.GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

  mongocxx::cursor cursor_user = user.GetCollection().find(filter_view_email_password);

  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("premiumCard", card),
          bsoncxx::builder::basic::kvp("discountType", "premium"),
          bsoncxx::builder::basic::kvp("discount", GetCardDiscount(card)))));

  bsoncxx::document::view update_view = update_builder.view();
  user.GetCollection().update_one(filter_view_email_password, update_view);

  user.premium_card_ = card;
  User::discount_ = GetCardDiscount(card);
  User::discount_type_ = "premium";
  PrintSuccessMessage("Karta została przypisana do konta",
                      "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
}

void User::SetBlik(const std::string &payment_method) {
  if (payment_method_ == payment_method) {
    PrintErrorMessage("Wybrany sposób płatności jest już ustawiony.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection_.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  std::string repeated_password = DisplayMessageAndCaptureStringInput("Zmiana metody płatności",
                                                                      "Podaj ponownie nowe hasło żeby potwierdzić zmianę:");
  if (_password_ != repeated_password) {
    PrintErrorMessage("Podane hasła nie są takie same.", "Spróbuj ponownie.");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
              bsoncxx::builder::basic::kvp("type", "blik"))))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view_email_password, update_view);

  payment_method_ = payment_method;
  PrintSuccessMessage("Metoda płatności została pomyślnie zmieniona.", "");
}

void User::SetVisa(const std::string &card_number, const std::string &card_cvv) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection_.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  // sprawdzenie, czy taka karta już istnieje
  bsoncxx::document::value filter_builder_card_cvv = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("paymentMethod.cardNumber", card_number),
      bsoncxx::builder::basic::kvp("paymentMethod.cvv", card_cvv));

  bsoncxx::document::view filter_view_card_cvv = filter_builder_card_cvv.view();
  mongocxx::cursor cursor_card_cvv = _collection_.find(filter_view_card_cvv);
  if (cursor_card_cvv.begin() != cursor_card_cvv.end()) {
    PrintErrorMessage("Karta już istnieje w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
              bsoncxx::builder::basic::kvp("type", "visa"),
              bsoncxx::builder::basic::kvp("cardNumber", card_number),
              bsoncxx::builder::basic::kvp("cvv", card_cvv))))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view_email_password, update_view);

  payment_method_ = "visa";
  PrintSuccessMessage("Metoda płatności została pomyślnie zmieniona.", "");
}

// Loty użytkownika (bilety, bagaż, odprawa)

void User::AddTicketToUser(const std::vector<int> &seats, const FlightConnection &flight_connection) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("ticketBought", ticket_bought_ + (int) seats.size()))));

  ticket_bought_ += (int) seats.size();

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view, update_view);

  bsoncxx::builder::basic::array seats_array;
  for (const auto &seat : seats) {
    seats_array.append(seat);
  }

  std::string flight_id = flight_connection.GetIdentifier();
  std::string departure_city = flight_connection.GetDepartureCity();
  std::string destination_city = flight_connection.GetDestinationCity();
  std::string departure_time = flight_connection.GetDepartureTime();
  std::string arrival_time = flight_connection.GetArrivalTime();
  auto flight_price = flight_connection.GetPrice();

  bsoncxx::document::value ticket_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("flightId", flight_id),
      bsoncxx::builder::basic::kvp("departure", departure_city),
      bsoncxx::builder::basic::kvp("destination", destination_city),
      bsoncxx::builder::basic::kvp("departureTime", departure_time),
      bsoncxx::builder::basic::kvp("arrivalTime", arrival_time),
      bsoncxx::builder::basic::kvp("price", flight_price),
      bsoncxx::builder::basic::kvp("seats", seats_array),
      bsoncxx::builder::basic::kvp("checkin", false),
      bsoncxx::builder::basic::kvp("luggageCheckin", false));

  bsoncxx::document::view ticket_view = ticket_builder.view();
  _collection_.update_one(filter_view, bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$push", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("userFlights", ticket_view)))));

  if (seats.size() == 1) {
    PrintSuccessMessage("Bilet został pomyślnie zakupiony.", "Możesz zobaczyć go w zakładce 'Moje bilety'.");
  } else {
    PrintSuccessMessage("Bilety zostały pomyślnie zakupione.", "Możesz zobaczyć je w zakładce 'Moje bilety'.");
  }
}

void User::UpdateMoneySaved(double normal_price, double discount_price) {
  double saved = normal_price - discount_price;
  money_saved_ += saved;

  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("moneySaved", money_saved_ += saved))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection_.update_one(filter_view, update_view);
}

void User::LuggageCheckin(int flight_number) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email_),
      bsoncxx::builder::basic::kvp("password", GetPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection_.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::view user_view = *cursor.begin();
  bsoncxx::document::element user_flights_element = user_view["userFlights"];
  bsoncxx::array::view user_flights = user_flights_element.get_array().value;

  int flight_index = flight_number - 1;

  // sprawdź, czy bagaż dla tego lotu jest już odprawiony
  if (user_flights[flight_index]["luggageCheckin"].get_bool().value) {
    PrintErrorMessage("Ten lot został już odprawiony.", "Wybierz inny lot.");
    return;
  }

  // zaktualizuj wartość w tym arrayu o podanym indeksie na true
  bsoncxx::builder::basic::document update_builder;
  std::string updateKey = "userFlights." + std::to_string(flight_index) + ".luggageCheckin";
  update_builder.append(bsoncxx::builder::basic::kvp(updateKey, true));
  bsoncxx::document::value update = update_builder.extract();

  bsoncxx::builder::basic::document update_doc_builder;
  update_doc_builder.append(bsoncxx::builder::basic::kvp("$set", update));
  bsoncxx::document::value update_doc = update_doc_builder.extract();

  _collection_.update_one(filter_view, update_doc.view());

  PrintSuccessMessage("Bagaż został odprawiony pomyślnie!", "Życzymy udanego lotu!");
}
