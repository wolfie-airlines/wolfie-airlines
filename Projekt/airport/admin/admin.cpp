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
                                                        || input == "matematyk" || input == "back";
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
  std::string
      item_name = CaptureLineWithValidation("Dodawanie przedmiotu", "Podaj nazwę przedmiotu:", ValidateNonEmpty);
  if (item_name.empty() || item_name == "back") return;

  std::string
      item_description = CaptureLineWithValidation("Dodawanie przedmiotu", "Podaj opis przedmiotu:", ValidateNonEmpty);
  if (item_description.empty() || item_description == "back") return;

  std::string hints_str =
      CaptureLineWithValidation("Dodawanie przedmiotu", "Podaj ważne informacje (oddzielone średnikiem) (jeśli brak: wpisz \"brak\")", ValidateNonEmpty);
  std::vector<std::string> hints;
  if (!hints_str.empty() && hints_str != "back" && hints_str != "brak") {
    std::stringstream ss(hints_str);
    std::string hint;
    while (std::getline(ss, hint, ';')) {
      hints.push_back(hint);
    }
  }

  std::optional<bool> is_banned = CaptureBoolWithValidation("Dodawanie przedmiotu",
                                                            "Czy przedmiot jest zabroniony w transporcie lotniczym? (tak/nie):");
  if (!is_banned.has_value()) return;
  std::optional<bool> requires_approval =
      CaptureBoolWithValidation("Dodawanie przedmiotu", "Czy przedmiot wymaga zgody przewoźnika? (tak/nie):");
  if (!requires_approval.has_value()) return;
  std::optional<bool> in_checked_luggage = CaptureBoolWithValidation("Dodawanie przedmiotu",
                                                                     "Czy przedmiot może być przewożony w bagażu rejestrowanym? (tak/nie):");
  if (!in_checked_luggage.has_value()) return;
  std::optional<bool> in_hand_luggage = CaptureBoolWithValidation("Dodawanie przedmiotu",
                                                                  "Czy przedmiot może być przewożony w bagażu podręcznym? (tak/nie):");
  if (!in_hand_luggage.has_value()) return;
  std::optional<bool> inform_pilot = CaptureBoolWithValidation("Dodawanie przedmiotu",
                                                               "Czy pilot musi zostać poinformowany o przewożeniu tego przedmiotu? (tak/nie):");
  if (!inform_pilot.has_value()) return;

  std::string max_quantity_str =
      CaptureInputWithValidation("Dodawanie przedmiotu", "Podaj maksymalną ilość na osobę:", ValidatePrice);
  if (max_quantity_str.empty() || max_quantity_str == "back") return;
  int max_quantity = std::stoi(max_quantity_str);

  std::string avg_weight_str = CaptureInputWithValidation("Dodawanie przedmiotu",
                                                          "Podaj uśrednioną wagę jednego przedmiotu takiego typu:",
                                                          ValidatePrice);
  if (avg_weight_str.empty() || avg_weight_str == "back") return;
  double avg_weight = std::stod(avg_weight_str);

  bsoncxx::builder::basic::array hints_builder{};
  for (const auto &hint : hints) {
    hints_builder.append(hint);
  }

  bsoncxx::builder::basic::document item_builder{};
  item_builder.append(bsoncxx::builder::basic::kvp("item", item_name),
                      bsoncxx::builder::basic::kvp("description", item_description),
                      bsoncxx::builder::basic::kvp("hints", hints_builder),
                      bsoncxx::builder::basic::kvp("forbidden", is_banned.value()),
                      bsoncxx::builder::basic::kvp("operatorAllowance", requires_approval.value()),
                      bsoncxx::builder::basic::kvp("registeredLuggage", in_checked_luggage.value()),
                      bsoncxx::builder::basic::kvp("handLuggage", in_hand_luggage.value()),
                      bsoncxx::builder::basic::kvp("pilotAllowance", inform_pilot.value()),
                      bsoncxx::builder::basic::kvp("maxCount", max_quantity),
                      bsoncxx::builder::basic::kvp("weightForOne", avg_weight));

  auto collection = user.GetSpecificCollection("luggage_list");
  collection.insert_one(item_builder.view());

  PrintSuccessMessage("Przedmiot został dodany pomyślnie", "");
}