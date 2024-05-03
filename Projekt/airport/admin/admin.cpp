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

void Admin::AddVerificationQuestion(User &user) {
  std::string domain = CaptureInputWithValidation("Dodawanie pytania",
                                                  "Wybierz dziedzinę (doktor, informatyk, matematyk):",
                                                  [](const std::string &input) {
                                                    return input == "doktor" || input == "informatyk"
                                                        || input == "matematyk";
                                                  });
  if (domain.empty() || domain == "back") return;

  std::string collection_name;
  bsoncxx::builder::basic::document question_builder{};

  if (domain == "doktor") {
    collection_name = "doctor-question";
    std::string question = CaptureLineWithValidation("Dodawanie pytania", "Podaj treść pytania:", ValidateNonEmpty);
    if (question.empty() || question == "back") return;
    std::string answer = CaptureLineWithValidation("Dodawanie pytania", "Podaj odpowiedź:", ValidateNonEmpty);
    if (answer.empty() || answer == "back") return;

    question_builder.append(bsoncxx::builder::basic::kvp("question", question),
                            bsoncxx::builder::basic::kvp("answer", answer));
  } else if (domain == "informatyk") {
    collection_name = "informatic-questions";
    std::string
        language = CaptureInputWithValidation("Dodawanie pytania", "Podaj język programowania:", ValidateNonEmpty);
    if (language.empty() || language == "back") return;
    std::string error = CaptureLineWithValidation("Dodawanie pytania", "Podaj błąd w kodzie:", ValidateNonEmpty);
    if (error.empty() || error == "back") return;
    std::string wrong_code = CaptureLineWithValidation("Dodawanie pytania", "Podaj BŁĘDNY kod:", ValidateNonEmpty);
    if (wrong_code.empty() || wrong_code == "back") return;
    std::string
        answer_str = CaptureInputWithValidation("Dodawanie pytania", "Podaj odpowiedź (numer linii):", ValidatePrice);
    if (answer_str.empty() || answer_str == "back") return;

    int answer = std::stoi(answer_str);

    question_builder.append(bsoncxx::builder::basic::kvp("language", language),
                            bsoncxx::builder::basic::kvp("error", error),
                            bsoncxx::builder::basic::kvp("code", wrong_code),
                            bsoncxx::builder::basic::kvp("answer", answer));
  } else if (domain == "matematyk") {
    collection_name = "math-questions";
    std::string
        problem_title = CaptureLineWithValidation("Dodawanie pytania", "Podaj tytuł problemu:", ValidateNonEmpty);
    if (problem_title.empty() || problem_title == "back") return;
    std::string
        problem_description = CaptureLineWithValidation("Dodawanie pytania", "Podaj opis problemu:", ValidateNonEmpty);
    if (problem_description.empty() || problem_description == "back") return;
    std::string
        hint = CaptureLineWithValidation("Dodawanie pytania", "Podaj podpowiedź:", ValidateNonEmpty);
    if (hint.empty() || hint == "back") return;

    std::string solution = CaptureLineWithValidation("Dodawanie pytania", "Podaj rozwiązanie:", ValidateSolution);
    if (solution.empty() || solution == "back") return;

    question_builder.append(bsoncxx::builder::basic::kvp("problem", problem_title),
                            bsoncxx::builder::basic::kvp("description", problem_description),
                            bsoncxx::builder::basic::kvp("hint", hint));

    try {
      int solution_int = std::stoi(solution);
      question_builder.append(bsoncxx::builder::basic::kvp("solution", solution_int));
    } catch (std::invalid_argument &e) {
      try {
        double solution_double = std::stod(solution);
        question_builder.append(bsoncxx::builder::basic::kvp("solution", solution_double));
      } catch (std::invalid_argument &e) {
        question_builder.append(bsoncxx::builder::basic::kvp("solution", solution));
      }
    }
  }

  auto collection = user.GetSpecificCollection(collection_name);
  collection.insert_one(question_builder.view());

  PrintSuccessMessage("Pytanie zostało dodane pomyślnie", "");
}

void Admin::ManageUsers(User &user) {
  // TODO
}

void Admin::AddLuggageItem(User &user) {
  // TODO
}