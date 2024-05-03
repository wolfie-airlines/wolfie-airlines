#include "admin.h"
#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "admin_functions/admin_functions.h"

#include <utility>

Admin::Admin(const std::string &username,
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
             std::string hashed_admin_password)
    : User(username,
           email,
           discount,
           discount_type,
           premium_card,
           payment_method,
           client,
           profession,
           registration_date,
           money_spent,
           money_saved,
           ticket_bought,
           user_flights,
           is_admin), hashed_admin_password_(std::move(hashed_admin_password)) {}

void Admin::AddFlight(User &user) {
  std::string choice = ProcessAddingFlight();

  if (choice == "dalej") {
    auto collection = user.GetSpecificCollection("flight_connections");
    std::string flight_id = CaptureInputWithValidation("Dodawanie lotu", "Podaj ID lotu:", ValidateFlightId);
    if (flight_id.empty()) return;

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("identifier", flight_id));

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = collection.find(filter_view);
    if (cursor.begin() != cursor.end()) {
      PrintErrorMessage("Lot o podanym ID już istnieje.", "Nie może być 2 lotów o tym samym unikalnym ID.");
      return;
    }

    std::string departure = CaptureInputWithValidation("Dodawanie lotu", "Podaj miasto wylotu:", ValidateCity);
    if (departure.empty()) return;

    std::string arrival = CaptureInputWithValidation("Dodawanie lotu", "Podaj miasto przylotu:", ValidateCity);
    if (arrival.empty()) return;

    std::string
        departure_date = CaptureInputWithValidation("Dodawanie lotu", "Podaj datę wylotu (DD.MM.YYYY):", ValidateDate);
    if (departure_date.empty()) return;

    std::string
        departure_time = CaptureInputWithValidation("Dodawanie lotu", "Podaj godzinę wylotu (HH:MM):", ValidateTime);
    if (departure_time.empty()) return;

    std::string
        arrival_date = CaptureInputWithValidation("Dodawanie lotu", "Podaj datę przylotu (DD.MM.YYYY):", ValidateDate);
    if (arrival_date.empty()) return;

    std::string
        arrival_time = CaptureInputWithValidation("Dodawanie lotu", "Podaj godzinę przylotu (HH:MM):", ValidateTime);
    if (arrival_time.empty()) return;

    std::string price = CaptureInputWithValidation("Dodawanie lotu", "Podaj cenę biletu:", ValidatePrice);
    if (price.empty()) return;

    int price_int = std::stoi(price);

    bsoncxx::document::value flight_builder = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("identifier", flight_id),
        bsoncxx::builder::basic::kvp("departureCity", departure),
        bsoncxx::builder::basic::kvp("destinationCity", arrival),
        bsoncxx::builder::basic::kvp("departureTime", departure_date + " " + departure_time),
        bsoncxx::builder::basic::kvp("arrivalTime", arrival_date + " " + arrival_time),
        bsoncxx::builder::basic::kvp("price", price_int),
        bsoncxx::builder::basic::kvp("availableSeats", 81),
        bsoncxx::builder::basic::kvp("seatsTaken", bsoncxx::builder::basic::make_array().view())
    );

    collection.insert_one(flight_builder.view());

    PrintSuccessMessage("Lot został dodany pomyślnie", "");

  } else if (choice == "quit") {
    PrintErrorMessage("Przerwano dodawanie lotu", "");
    return;
  } else {
    PrintErrorMessage("Nieprawidłowy wybór", "Nastąpił powrót do menu administratora.");
    return;
  }
}

void Admin::AddVerificationQuestion() {
  // TODO
}

void Admin::ManageUsers() {
  // TODO
}