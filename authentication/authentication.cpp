#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#include "authentication.h"
#include "../functions/info_prints/info_prints.h"
#include <future>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

Authentication::Authentication(const std::string &uri_str,
                               const std::string &db_name,
                               const std::string &collection_name)
    : _client_{mongocxx::uri{uri_str}}, _db_{_client_[db_name]}, _collection_{_db_[collection_name]} {}

std::string Authentication::HashPassword(const std::string &password) {
  CryptoPP::SHA256 hash;
  std::string digest;

  CryptoPP::StringSource
      s(password, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
  return digest;
}

bool Authentication::RegisterUser(const std::string &username, const std::string &email, const std::string &password) {

  std::string hashed_password = HashPassword(password);

  auto usernameAlreadyExists =
      _collection_.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username)));
  if (usernameAlreadyExists) {
    PrintErrorMessage("Podana nazwa użytkownika jest już zajęta.", "Wybierz inną nazwę.");
    return false;
  }

  auto email_already_exists =
      _collection_.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("email_", email)));
  if (email_already_exists) {
    PrintErrorMessage("Podany adres e-mail jest już zajęty.", "Wybierz inny adres e-mail.");
    return false;
  }

  auto document = bsoncxx::builder::basic::document{};
  document.append(bsoncxx::builder::basic::kvp("username", username));
  document.append(bsoncxx::builder::basic::kvp("email", email));
  document.append(bsoncxx::builder::basic::kvp("password", hashed_password));
  document.append(bsoncxx::builder::basic::kvp("profession", "brak"));
  document.append(bsoncxx::builder::basic::kvp("premiumCard", "brak"));
  document.append(bsoncxx::builder::basic::kvp("moneySpent", 0.00));
  document.append(bsoncxx::builder::basic::kvp("moneySaved", 0.00));
  document.append(bsoncxx::builder::basic::kvp("ticketBought", 0));
  document.append(bsoncxx::builder::basic::kvp("discountType", "brak"));
  document.append(bsoncxx::builder::basic::kvp("discount", 1.00));


  // Pobieranie daty i godziny rejestracji (potrzebne do statystyk w profilu)
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  std::tm tm;
  localtime_s(&tm, &in_time_t);
  ss << std::put_time(&tm, "%H:%M %d.%m.%Y");
  std::string dateTime = ss.str();
  document.append(bsoncxx::builder::basic::kvp("registrationDate", dateTime));

  auto payment_method_document = bsoncxx::builder::basic::document{};
  payment_method_document.append(bsoncxx::builder::basic::kvp("type", "blik"));
  payment_method_document.append(bsoncxx::builder::basic::kvp("cardNumber",
                                                            bsoncxx::types::b_null{})); // null jako wartosci, bo do blika niepotrzebne
  payment_method_document.append(bsoncxx::builder::basic::kvp("cvv", bsoncxx::types::b_null{}));

  document.append(bsoncxx::builder::basic::kvp("paymentMethod", payment_method_document));

  auto userFlights = bsoncxx::builder::basic::array{};
  document.append(bsoncxx::builder::basic::kvp("userFlights", userFlights));

  auto result = _collection_.insert_one(document.view());
  return result ? true : false;
}

void Authentication::AuthenticateUser(const std::string &username,
                                      const std::string &password,
                                      std::promise<bool> &&promise,
                                      User &user) {
  std::string hashed_password = HashPassword(password);
  auto document = bsoncxx::builder::basic::document{};
  document.append(bsoncxx::builder::basic::kvp("username", username));
  document.append(bsoncxx::builder::basic::kvp("password", hashed_password));

  auto result = _collection_.find_one(document.view());
  if (result) {
    bsoncxx::document::view userView = result->view();
    auto payment_method_document = userView["paymentMethod"].get_document().value;
    auto user_flights_document = userView["userFlights"].get_array().value;
    auto email = (std::string) userView["email"].get_string().value;
    auto premium_card = (std::string) userView["premiumCard"].get_string().value;
    auto payment_method = payment_method_document["type"].get_string().value;
    auto money_spent = userView["moneySpent"].get_double().value;
    auto money_saved = userView["moneySaved"].get_double().value;
    auto ticket_bought = userView["ticketBought"].get_int32().value;
    auto registration_date = (std::string) userView["registrationDate"].get_string().value;
    auto discount_type = (std::string) userView["discountType"].get_string().value;
    auto discount = userView["discount"].get_double().value;
    user.username_ = username;
    user.SetPassword(password);
    user.discount_ = discount;
    user.email_ = email;
    user.discount_type_ = discount_type;
    user.profession_ = static_cast<std::string>(userView["profession"].get_string().value);
    user.premium_card_ = premium_card;
    user.payment_method_ = static_cast<std::string>(payment_method);
    user.money_spent_ = money_spent;
    user.money_saved_ = money_saved;
    user.ticket_bought_ = ticket_bought;
    user.registration_date_ = registration_date;
    std::vector<bsoncxx::document::value> user_flights;
    bsoncxx::array::view user_flights_array = user_flights_document;
    for (auto &&userFlight : user_flights_array) {
      user_flights.push_back(static_cast<bsoncxx::document::value>(userFlight.get_document().value));
    }
    user.user_flights_ = user_flights;
    promise.set_value(true);
    PrintSuccessMessage("Zalogowano pomyślnie.", "Witamy w systemie.");
  } else {
    PrintErrorMessage("Wprowadzono niepoprawne dane bądź taki użytkownik nie istnieje.", "");
    promise.set_value(false);
  }
}

#pragma clang diagnostic pop