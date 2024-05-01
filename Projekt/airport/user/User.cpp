#include "User.h"

#include <utility>

#include "../admin/Admin.h"
#include "../env/EnvParser.h"
#include "../functions/helpers.h"
#include "../functions/info_print_functions.h"
#include "bsoncxx/json.hpp"
#include "premium_cards/premium_cards.h"

User::User(std::string username, std::string email, double discount, std::string discountType, std::string premiumCard,
           std::string paymentMethod, mongocxx::client &client, std::string profession,
           std::string registrationDate, double moneySpent, double moneySaved, int ticketBought,
           std::vector<bsoncxx::document::value> userFlights, bool isAdmin)
    : username(std::move(username)),
      email(std::move(email)),
      discount(discount),
      discountType(std::move(discountType)),
      premiumCard(std::move(premiumCard)),
      paymentMethod(std::move(paymentMethod)),
      _client(client),
      profession(std::move(profession)),
      registrationDate(std::move(registrationDate)),
      moneySpent(moneySpent),
      moneySaved(moneySaved),
      ticketBought(ticketBought),
      userFlights(std::move(userFlights)),
      isAdmin(isAdmin) {}

// Resetowanie użytkownika
void User::reset() {
  username = "gosc";
  email = "brak";
  discount = 1.0;
  discountType = "brak";
  premiumCard = "brak";
  paymentMethod = "blik";
  profession = "brak";
  registrationDate = "brak";
  moneySpent = 0;
  moneySaved = 0;
  ticketBought = 0;
  userFlights.clear();
  isAdmin = false;
}

// Zwracanie kolekcji użytkownika/za pomocą klasy użytkownika
mongocxx::collection &User::getCollection() {
  return _collection;
}

mongocxx::collection User::getSpecificCollection(const std::string &collectionName) {
  return _db[collectionName];
}

mongocxx::cursor User::findUserInDatabase() {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();

  mongocxx::cursor cursor = _collection.find(filter_view);
  return cursor;
}

// Ustawienia
std::string User::getPassword() {
  std::string hashedPassword = hashString(password);
  return hashedPassword;
}

void User::setPassword(const std::string &newPass) {
  User::password = newPass;
}

void User::changePassword(const std::string &newPassword) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", password));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    std::cout << email << " " << password << std::endl;
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  std::cout << "Podaj ponownie nowe hasło żeby potwierdzić zmianę: ";
  std::string repeatedPassword;
  std::cin >> repeatedPassword;
  if (newPassword != repeatedPassword) {
    errorFunction("Podane hasła nie są takie same.", "Spróbuj ponownie.");
    return;
  }

  std::cout << "Podaj stare hasło żebyśmy mieli 200% pewności że to ty: ";
  std::string oldPassword;
  std::cin >> oldPassword;
  if (oldPassword != password) {
    errorFunction("Podane hasło nie jest poprawne.", "Spróbuj ponownie.");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("password", newPassword))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view_email_password, update_view);

  password = newPassword;
  validFunction("Hasło zostało pomyślnie zmienione.", "");
}

void User::changeUsername(const std::string &newUsername) {
  // sprawdzenie czy nazwa jest zajeta
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("username", newUsername));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection.find(filter_view);
  if (cursor.begin() != cursor.end()) {
    errorFunction("Nazwa użytkownika jest już zajęta.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", password));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    std::cout << email << " " << password << std::endl;
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("username", newUsername))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view_email_password, update_view);

  username = newUsername;
  validFunction("Nazwa użytkownika została pomyślnie zmieniona.", "");
}

void User::changeEmail(const std::string &newEmail) {
  // sprawdzanie czy email jest zajety
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", newEmail));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection.find(filter_view);
  if (cursor.begin() != cursor.end()) {
    errorFunction("Ten adres e-mail jest już zajęty.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", password));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    std::cout << email << " " << password << std::endl;
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("email", newEmail))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view_email_password, update_view);

  email = newEmail;
  validFunction("Adres e-mail został pomyślnie zmieniony.", "");
}

bool User::checkIfAdmin() const {
  return isAdmin;
}

void User::loginAsAdmin() {
  if (isAdmin) {
    errorFunction("Jesteś już zalogowany jako administrator.", "");
    return;
  }
  EnvParser envParser;
  envParser.parseEnvFile();
  std::string adminPassword = envParser.getValue("ADMIN_PASSWORD");
  std::string adminPasswordHashed = hashString(adminPassword);

  std::cout << "Podaj hasło administratora: ";
  std::string providedPassword;
  std::cin >> providedPassword;

  std::string providedPasswordHashed = hashString(providedPassword);

  if (providedPasswordHashed == adminPasswordHashed) {
    validFunction("Zalogowano jako administrator.", "");
    Admin admin = Admin(username,
                        email,
                        discount,
                        discountType,
                        premiumCard,
                        paymentMethod,
                        _client,
                        profession,
                        registrationDate,
                        moneySpent,
                        moneySaved,
                        ticketBought,
                        userFlights,
                        true,
                        adminPasswordHashed);
    setIsAdmin(true);
  } else {
    errorFunction("Błędne hasło administratora.", "");
  }
}

// Płatności użytkownika (zniżki, ulgi, płatności kartą/blikiem)

double User::getDiscount() const {
  return discount;
}

std::string User::recognizeDiscount() const {
  double disc = getDiscount();
  if (disc == 0.05) {
    return "Weteran wojenny";
  } else if (disc == 0.4) {
    return "Osoba niepełnosprawna";
  } else if (disc == 0.45) {
    return "Emeryt";
  } else if (disc == 0.49) {
    return "Student";
  } else {
    return "brak";
  }
}

void User::setDiscount(double disc, const std::string &discType) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

  mongocxx::cursor cursor_user = findUserInDatabase();

  if (cursor_user.begin() == cursor_user.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("discountType", discType),
          bsoncxx::builder::basic::kvp("discount", disc))));

  bsoncxx::document::view update_view = update_builder.view();
  getCollection().update_one(filter_view_email_password, update_view);
  User::discount = disc;
  User::discountType = discType;
  validFunction("Zniżka została przypisana do konta", "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
}

void User::setPremiumCard(User &user, const std::string &card) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", user.email),
      bsoncxx::builder::basic::kvp("password", user.getPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

  mongocxx::cursor cursor_user = user.getCollection().find(filter_view_email_password);

  if (cursor_user.begin() == cursor_user.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("premiumCard", card),
          bsoncxx::builder::basic::kvp("discountType", "premium"),
          bsoncxx::builder::basic::kvp("discount", getCardDiscount(card)))));

  bsoncxx::document::view update_view = update_builder.view();
  user.getCollection().update_one(filter_view_email_password, update_view);

  user.premiumCard = card;
  User::discount = getCardDiscount(card);
  User::discountType = "premium";
  validFunction("Karta została przypisana do konta", "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
}

void User::setBlik(const std::string &payment) {
  if (paymentMethod == payment) {
    errorFunction("Wybrany sposób płatności jest już ustawiony.", "");
    return;
  }

  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  std::cout << "Podaj ponownie nowe hasło żeby potwierdzić zmianę: ";
  std::string repeatedPassword;
  std::cin >> repeatedPassword;
  if (password != repeatedPassword) {
    errorFunction("Podane hasła nie są takie same.", "Spróbuj ponownie.");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
              bsoncxx::builder::basic::kvp("type", "blik"))))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view_email_password, update_view);

  paymentMethod = payment;
  validFunction("Metoda płatności została pomyślnie zmieniona.", "");
}

void User::setVisa(const std::string &cardNumber, const std::string &cvv) {
  bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
  mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
  if (cursor_user.begin() == cursor_user.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  // sprawdzenie czy taka karta już istnieje
  bsoncxx::document::value filter_builder_card_cvv = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("paymentMethod.cardNumber", cardNumber),
      bsoncxx::builder::basic::kvp("paymentMethod.cvv", cvv));

  bsoncxx::document::view filter_view_card_cvv = filter_builder_card_cvv.view();
  mongocxx::cursor cursor_card_cvv = _collection.find(filter_view_card_cvv);
  if (cursor_card_cvv.begin() != cursor_card_cvv.end()) {
    errorFunction("Karta już istnieje w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
              bsoncxx::builder::basic::kvp("type", "visa"),
              bsoncxx::builder::basic::kvp("cardNumber", cardNumber),
              bsoncxx::builder::basic::kvp("cvv", cvv))))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view_email_password, update_view);

  paymentMethod = "visa";
  validFunction("Metoda płatności została pomyślnie zmieniona.", "");
}

// Loty użytkownika (bilety, bagaż, odprawa)

void User::addTicketToUser(const std::vector<int> &seats, const FlightConnection &flightConnection) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("ticketBought", ticketBought + (int) seats.size()))));

  ticketBought += (int) seats.size();

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view, update_view);

  bsoncxx::builder::basic::array seats_array;
  for (const auto &seat : seats) {
    seats_array.append(seat);
  }

  std::string flightId = flightConnection.getIdentifier();
  std::string departure = flightConnection.getDepartureCity();
  std::string destination = flightConnection.getDestinationCity();
  std::string departureTime = flightConnection.getDepartureTime();
  std::string arrivalTime = flightConnection.getArrivalTime();
  auto flightPrice = flightConnection.getPrice();

  bsoncxx::document::value ticket_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("flightId", flightId),
      bsoncxx::builder::basic::kvp("departure", departure),
      bsoncxx::builder::basic::kvp("destination", destination),
      bsoncxx::builder::basic::kvp("departureTime", departureTime),
      bsoncxx::builder::basic::kvp("arrivalTime", arrivalTime),
      bsoncxx::builder::basic::kvp("price", flightPrice),
      bsoncxx::builder::basic::kvp("seats", seats_array),
      bsoncxx::builder::basic::kvp("checkin", false),
      bsoncxx::builder::basic::kvp("luggageCheckin", false));

  bsoncxx::document::view ticket_view = ticket_builder.view();
  _collection.update_one(filter_view, bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$push", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("userFlights", ticket_view)))));

  if (seats.size() == 1) {
    validFunction("Bilet został pomyślnie zakupiony.", "Możesz zobaczyć go w zakładce 'Moje bilety'.");
  } else {
    validFunction("Bilety zostały pomyślnie zakupione.", "Możesz zobaczyć je w zakładce 'Moje bilety'.");
  }
}

void User::updateMoneySaved(double normPrice, double discPrice) {
  double saved = normPrice - discPrice;
  moneySaved += saved;

  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
          bsoncxx::builder::basic::kvp("moneySaved", moneySaved += saved))));

  bsoncxx::document::view update_view = update_builder.view();
  _collection.update_one(filter_view, update_view);
}

void User::luggageCheckin(int flightNumber) {
  bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("email", email),
      bsoncxx::builder::basic::kvp("password", getPassword()));

  bsoncxx::document::view filter_view = filter_builder.view();
  mongocxx::cursor cursor = _collection.find(filter_view);
  if (cursor.begin() == cursor.end()) {
    errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
    return;
  }

  bsoncxx::document::view userView = *cursor.begin();
  bsoncxx::document::element userFlightsElement = userView["userFlights"];
  bsoncxx::array::view userFlightsArray = userFlightsElement.get_array().value;

  // w całym arrayu znajdź index lotu który ma numer flightNumber -1
  int flightIndex = flightNumber - 1;

  // sprawdź czy bagaż dla tego lotu jest już odprawiony
  if (userFlightsArray[flightIndex]["luggageCheckin"].get_bool().value) {
    errorFunction("Ten lot został już odprawiony.", "Wybierz inny lot.");
    return;
  }

  // zaktualizuj wartość w tym arrayu o podanym indeksie na true
  bsoncxx::builder::basic::document update_builder;
  std::string updateKey = "userFlights." + std::to_string(flightIndex) + ".luggageCheckin";
  update_builder.append(bsoncxx::builder::basic::kvp(updateKey, true));
  bsoncxx::document::value update = update_builder.extract();

  bsoncxx::builder::basic::document update_doc_builder;
  update_doc_builder.append(bsoncxx::builder::basic::kvp("$set", update));
  bsoncxx::document::value update_doc = update_doc_builder.extract();

  _collection.update_one(filter_view, update_doc.view());

  validFunction("Bagaż został odprawiony pomyślnie!", "Życzymy udanego lotu!");
}
