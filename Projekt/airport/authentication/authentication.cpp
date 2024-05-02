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

  std::string hashedPassword = HashPassword(password);

  auto usernameAlreadyExists =
      _collection_.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("username", username)));
  if (usernameAlreadyExists) {
    PrintErrorMessage("Podana nazwa użytkownika jest już zajęta.", "Wybierz inną nazwę.");
    return false;
  }

  auto emailAlreadyExists =
      _collection_.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("email_", email)));
  if (emailAlreadyExists) {
    PrintErrorMessage("Podany adres e-mail jest już zajęty.", "Wybierz inny adres e-mail.");
    return false;
  }

  auto document = bsoncxx::builder::basic::document{};
  document.append(bsoncxx::builder::basic::kvp("username", username));
  document.append(bsoncxx::builder::basic::kvp("email", email));
  document.append(bsoncxx::builder::basic::kvp("password", hashedPassword));
  document.append(bsoncxx::builder::basic::kvp("profession", "brak"));
  document.append(bsoncxx::builder::basic::kvp("premiumCard", "brak"));
  document.append(bsoncxx::builder::basic::kvp("moneySpent", 0.00));
  document.append(bsoncxx::builder::basic::kvp("moneySaved", 0.00));
  document.append(bsoncxx::builder::basic::kvp("ticketBought", 0));
  document.append(bsoncxx::builder::basic::kvp("discountType", "brak"));
  document.append(bsoncxx::builder::basic::kvp("discount", 1.00));


  // Pobieranie daty i godziny rejestracji - potrzebne do statystyk w profilu
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%H:%M %d.%m.%Y");
  std::string dateTime = ss.str();
  document.append(bsoncxx::builder::basic::kvp("registrationDate", dateTime));

  auto paymentMethodDocument = bsoncxx::builder::basic::document{};
  paymentMethodDocument.append(bsoncxx::builder::basic::kvp("type", "blik"));
  paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cardNumber",
                                                            bsoncxx::types::b_null{})); // null jako wartosci, bo do blika niepotrzebne
  paymentMethodDocument.append(bsoncxx::builder::basic::kvp("cvv", bsoncxx::types::b_null{}));

  document.append(bsoncxx::builder::basic::kvp("paymentMethod", paymentMethodDocument));

  auto userFlights = bsoncxx::builder::basic::array{};
  document.append(bsoncxx::builder::basic::kvp("userFlights", userFlights));

  auto result = _collection_.insert_one(document.view());
  return result ? true : false;
}

void Authentication::AuthenticateUser(const std::string &username,
                                      const std::string &password,
                                      std::promise<bool> &&promise,
                                      User &user) {
  std::string hashedPassword = HashPassword(password);
  auto document = bsoncxx::builder::basic::document{};
  document.append(bsoncxx::builder::basic::kvp("username", username));
  document.append(bsoncxx::builder::basic::kvp("password", hashedPassword));

  auto result = _collection_.find_one(document.view());
  if (result) {
    bsoncxx::document::view userView = result->view();
    auto paymentMethodDocument = userView["paymentMethod"].get_document().value;
    auto userFlightsDocument = userView["userFlights"].get_array().value;
    auto email = (std::string) userView["email"].get_string().value;
    auto premiumCard = (std::string) userView["premiumCard"].get_string().value;
    auto paymentMethod = paymentMethodDocument["type"].get_string().value;
    auto moneySpent = userView["moneySpent"].get_double().value;
    auto moneySaved = userView["moneySaved"].get_double().value;
    auto ticketBought = userView["ticketBought"].get_int32().value;
    auto registrationDate = (std::string) userView["registrationDate"].get_string().value;
    auto discountType = (std::string) userView["discountType"].get_string().value;
    auto discount = userView["discount"].get_double().value;
    user.username_ = username;
    user.SetPassword(password);
    user.discount_ = discount;
    user.email_ = email;
    user.discount_type_ = discountType;
    user.profession_ = (std::string) userView["profession"].get_string().value;
    user.premium_card_ = premiumCard;
    user.payment_method_ = paymentMethod;
    user.money_spent_ = moneySpent;
    user.money_saved_ = moneySaved;
    user.ticket_bought_ = ticketBought;
    user.registration_date_ = registrationDate;
    std::vector<bsoncxx::document::value> userFlightsVector;
    bsoncxx::array::view userFlightsArray = userFlightsDocument;
    for (auto &&userFlight : userFlightsArray) {
      userFlightsVector.push_back(static_cast<bsoncxx::document::value>(userFlight.get_document().value));
    }
    user.user_flights_ = userFlightsVector;
    promise.set_value(true);
    PrintSuccessMessage("Zalogowano pomyślnie.", "Witamy w systemie.");
  } else {
    PrintErrorMessage("Wprowadzono niepoprawne dane bądź taki użytkownik nie istnieje.", "");
    promise.set_value(false);
  }
}
