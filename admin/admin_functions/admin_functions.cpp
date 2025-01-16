#include "admin_functions.h"

#include "validators.h"
#include "../admin.h"
#include "../../flights/flights_functions/flight_prints/flight_prints.h"
#include "../admin_prints/admin_prints.h"
#include "../../functions/info_prints/info_prints.h"
#include "managing_flights/flight_binary_tree.h"

std::string ProcessAddingFlight() {
  DisplayAddingFlightInfo();
  std::string input;
  std::cin >> input;
  return input;
}

void AddFlightToDatabase(User &user, BinaryTree<Flight> &flightTree) {
  auto collection = user.GetSpecificCollection("flight_connections");
    std::string flight_id = CaptureInputWithValidation("Dodawanie lotu", "Podaj ID lotu:", ValidateFlightId);
    if (flight_id.empty()) return;

    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp("identifier", flight_id));

    bsoncxx::document::view filter_view = filter_builder.view();
  if (mongocxx::cursor cursor = collection.find(filter_view); cursor.begin() != cursor.end()) {
      PrintErrorMessage("Lot o podanym ID już istnieje.", "Nie może być 2 lotów o tym samym unikalnym ID.");
      return;
    }

    std::string departure = CaptureLineWithValidation("Dodawanie lotu", "Podaj miasto wylotu:", ValidateCity);
    if (departure.empty()) return;

    std::string arrival = CaptureLineWithValidation("Dodawanie lotu", "Podaj miasto przylotu:", ValidateCity);
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
    int available_seats = 81;

    auto new_flight = std::make_shared<Flight>(flight_id, departure, arrival, departure_date + " " + departure_time, arrival_date + " " + arrival_time, available_seats, price_int);

    flightTree.addData(new_flight);

    PrintSuccessMessage("Lot został dodany pomyślnie", "");
}

void SearchFlight(const BinaryTree<Flight> &flightTree, User &user, FlightConnection &flight_connection) {
  const std::string search_id = CaptureInputWithValidation("Wyszukiwanie lotu", "Podaj ID lotu:", ValidateFlightId);
  if (const auto found_flight = flightTree.findDataById(search_id)) {
    PrintSuccessMessage("Znaleziono lot", "");
    auto found_connection = flight_connection.FindConnectionById(found_flight->flight_id);
    CreateFoundFlightScreen(found_connection, user);
  } else {
    PrintErrorMessage("Nie znaleziono lotu", "");
  }
}

void DeleteFlight(BinaryTree<Flight> &flightTree) {
  const std::string search_id = CaptureInputWithValidation("Usuwanie lotu", "Podaj ID lotu:", ValidateFlightId);
  if (const auto found_flight = flightTree.findDataById(search_id)) {
    flightTree.removeData(found_flight->flight_id);
    PrintSuccessMessage("Usunięto lot", "Lot " + found_flight->flight_id + " został pomyślnie usunięty.");
  } else {
    PrintErrorMessage("Nie znaleziono lotu", "");
  }
}

void HandleAdminDashboard(Admin &admin, User &user, FlightConnection &flight_connection) {
  DisplayAdminMenu();
  std::string option;
  std::cin >> option;
  BinaryTree<Flight> flightTree{user};

  while (option != "quit") {
     if (option == "1") {
      Admin::AddVerificationQuestion(user);
    } else if (option == "2") {
      Admin::ManageUsers(user);
    } else if (option == "3") {
      Admin::AddLuggageItem(user);
    } else if (option == "4") {
      if (std::string choice = ProcessAddingFlight(); choice == "dalej") {
    AddFlightToDatabase(user, flightTree);
  } else if (choice == "quit") {
    PrintErrorMessage("Przerwano dodawanie lotu", "");
    return;
  } else {
    PrintErrorMessage("Nieprawidłowy wybór", "Nastąpił powrót do menu administratora.");
    return;
  }
    } else if (option == "5") {
      DeleteFlight(flightTree);
    } else if (option == "6") {

      SearchFlight(flightTree, user, flight_connection);
    } else if (option == "7") {
      flightTree.serialize("flights.txt");
      DisplaySerializeMenu();
    } else {
      PrintErrorMessage("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
    DisplayAdminMenu();
    std::cin >> option;
  }
}


std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator) {
  std::string input = DisplayAdminMessageAndCaptureInput(title, message);
  while (!validator(input)) {
    PrintErrorMessage("Niepoprawne dane", message);
    if (input == "back") {
      PrintErrorMessage("Przerwano działanie administratora.", "Nastąpił powrót do panelu.");
      return "";
    }
    input = DisplayAdminMessageAndCaptureInput(title, message);
  }
  return input;
}

std::string CaptureLineWithValidation(const std::string &title,
                                      const std::string &message,
                                      const std::function<bool(const std::string &)> &validator) {
  std::string input = DisplayAdminMessageAndCaptureLine(title, message);
  while (!validator(input)) {
    PrintErrorMessage("Niepoprawne dane", message);
    if (input == "back") {
      PrintErrorMessage("Przerwano działanie administratora.", "Nastąpił powrót do panelu.");
      return "";
    }
    input = DisplayAdminMessageAndCaptureLine(title, message);
  }
  return input;
}

std::optional<bool> CaptureBoolWithValidation(const std::string &title, const std::string &message) {
  while (true) {
    std::string input = CaptureInputWithValidation(title, message, [](const std::string &input) {
      return input == "tak" || input == "nie" || input == "back";
    });
    if (input == "back") {
      PrintErrorMessage("Przerwano dodawanie przedmiotu", "Nastąpił powrót do panelu.");
      return std::nullopt;
    }
    if (input == "tak") return true;
    if (input == "nie") return false;
  }
}