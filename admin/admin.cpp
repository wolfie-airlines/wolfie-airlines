#include "admin.h"

#include <utility>

#include "../functions/info_prints/info_prints.h"
#include "../functions/main_prints/main_prints.h"
#include "admin_functions/admin_functions.h"
#include "admin_functions/validators.h"
#include "admin_prints/admin_prints.h"

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
           is_admin),
      hashed_admin_password_(std::move(hashed_admin_password)) {}

void Admin::AddFlight(User &user) {
    std::string choice = ProcessAddingFlight();

    if (choice == "dalej") {
        auto collection = user.GetSpecificCollection("flight_connections");
        std::string flight_id = CaptureInputWithValidation("Adding a flight", "Enter flight ID:", ValidateFlightId);
        if (flight_id.empty()) return;

        bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("identifier", flight_id));

        bsoncxx::document::view filter_view = filter_builder.view();
        mongocxx::cursor cursor = collection.find(filter_view);
        if (cursor.begin() != cursor.end()) {
            PrintErrorMessage("The flight with the specified ID already exists.", "There cannot be 2 flights with the same unique ID.");
            return;
        }

        std::string departure = CaptureInputWithValidation("Adding a flight", "Enter departure city:", ValidateCity);
        if (departure.empty()) return;

        std::string arrival = CaptureInputWithValidation("Adding a flight", "Enter destination city:", ValidateCity);
        if (arrival.empty()) return;

        std::string
            departure_date = CaptureInputWithValidation("Adding a flight", "Enter departure date (DD.MM.YYYY):", ValidateDate);
        if (departure_date.empty()) return;

        std::string
            departure_time = CaptureInputWithValidation("Adding a flight", "Enter departure hour (HH:MM):", ValidateTime);
        if (departure_time.empty()) return;

        std::string
            arrival_date = CaptureInputWithValidation("Adding a flight", "Enter arrival date (DD.MM.YYYY):", ValidateDate);
        if (arrival_date.empty()) return;

        std::string
            arrival_time = CaptureInputWithValidation("Adding a flight", "Enter arrival hour (HH:MM):", ValidateTime);
        if (arrival_time.empty()) return;

        std::string price = CaptureInputWithValidation("Adding a flight", "Enter flight price:", ValidatePrice);
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
            bsoncxx::builder::basic::kvp("seatsTaken", bsoncxx::builder::basic::make_array().view()));

        collection.insert_one(flight_builder.view());

        PrintSuccessMessage("Flight was added successfully", "");

    } else if (choice == "quit") {
        PrintErrorMessage("Interrupted adding a flight.", "");
        return;
    } else {
        PrintErrorMessage("Invalid selection.", "There has been return to the panel.");
        return;
    }
}

void Admin::AddVerificationQuestion(User &user) {
    std::string domain = CaptureInputWithValidation("Adding question",
                                                    "Choose a field (doctor, informatician, mathematician):",
                                                    [](const std::string &input) {
                                                        return input == "doctor" || input == "informatician" || input == "mathematician" || input == "back";
                                                    });
    if (domain.empty() || domain == "back") return;

    std::string collection_name;
    bsoncxx::builder::basic::document question_builder{};

    if (domain == "doctor") {
        collection_name = "doctor-question";
        std::string question = CaptureLineWithValidation("Adding question", "Etner the content of the question:", ValidateNonEmpty);
        if (question.empty() || question == "back") return;
        std::string answer = CaptureLineWithValidation("Adding question", "Enter answer:", ValidateNonEmpty);
        if (answer.empty() || answer == "back") return;

        question_builder.append(bsoncxx::builder::basic::kvp("question", question),
                                bsoncxx::builder::basic::kvp("answer", answer));
    } else if (domain == "informatyk") {
        collection_name = "informatic-questions";
        std::string
            language = CaptureInputWithValidation("Adding question", "Enter programming language:", ValidateNonEmpty);
        if (language.empty() || language == "back") return;
        std::string error = CaptureLineWithValidation("Adding question", "Enter code error:", ValidateNonEmpty);
        if (error.empty() || error == "back") return;
        std::string wrong_code = CaptureLineWithValidation("Adding question", "Enter INVALID code:", ValidateNonEmpty);
        if (wrong_code.empty() || wrong_code == "back") return;
        std::string
            answer_str = CaptureInputWithValidation("Adding question", "Enter solution (line number):", ValidatePrice);
        if (answer_str.empty() || answer_str == "back") return;

        int answer = std::stoi(answer_str);

        question_builder.append(bsoncxx::builder::basic::kvp("language", language),
                                bsoncxx::builder::basic::kvp("error", error),
                                bsoncxx::builder::basic::kvp("code", wrong_code),
                                bsoncxx::builder::basic::kvp("answer", answer));
    } else if (domain == "mathematician") {
        collection_name = "math-questions";
        std::string
            problem_title = CaptureLineWithValidation("Adding question", "Enter the title of the problem:", ValidateNonEmpty);
        if (problem_title.empty() || problem_title == "back") return;
        std::string
            problem_description = CaptureLineWithValidation("Adding question", "Enter the description of the problem:", ValidateNonEmpty);
        if (problem_description.empty() || problem_description == "back") return;
        std::string
            hint = CaptureLineWithValidation("Adding question", "Enter hint:", ValidateNonEmpty);
        if (hint.empty() || hint == "back") return;

        std::string solution = CaptureLineWithValidation("Adding question", "Enter solution:", ValidateSolution);
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

    PrintSuccessMessage("The question was added successfully.", "");
}

void Admin::ManageUsers(User &user) {
    DisplayManageUsersMenu();
    std::string option;
    std::cin >> option;

    while (option != "quit") {
        std::string username =
            CaptureInputWithValidation("User managment", "Enter user's username:", ValidateNonEmpty);
        if (username.empty() || username == "back") return;

        std::string
            email = CaptureInputWithValidation("User managment", "Enter user's e-mail:", ValidateNonEmpty);
        if (email.empty() || email == "back") return;

        auto collection = user.GetSpecificCollection("users");
        bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("username", username),
            bsoncxx::builder::basic::kvp("email", email));

        bsoncxx::document::view filter_view = filter_builder.view();
        mongocxx::cursor cursor = collection.find(filter_view);
        if (cursor.begin() == cursor.end()) {
            PrintErrorMessage("A user with the specified name and email was not found.", "Try again.");
            return;
        }

        if (option == "1") {
            std::string new_username =
                CaptureInputWithValidation("User managment", "Enter new user's username", ValidateNonEmpty);
            if (new_username.empty() || new_username == "back") return;
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "username",
                                                                                                              new_username)))));
        } else if (option == "2") {
            std::string new_email =
                CaptureInputWithValidation("User managment", "Enter new user's e-mail", ValidateNonEmpty);
            if (new_email.empty() || new_email == "back") return;
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "email",
                                                                                                              new_email)))));
        } else if (option == "3") {
            std::string new_profession =
                CaptureInputWithValidation("User managment", "Enter new user's job", ValidateNonEmpty);
            if (new_profession.empty() || new_profession == "back") return;
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "profession",
                                                                                                              new_profession)))));
        } else if (option == "4") {
            std::string new_premium_card = CaptureInputWithValidation("User managment",
                                                                      "Enter new user's premium card:",
                                                                      ValidateNonEmpty);
            if (new_premium_card.empty() || new_premium_card == "back") return;
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "premium_card",
                                                                                                              new_premium_card)))));
        } else if (option == "5") {
            std::string new_discount_type = CaptureInputWithValidation("User managment",
                                                                       "Enter new user's discount type (ulti/premium):",
                                                                       [](const std::string &input) {
                                                                           return input == "ulti" || input == "premium" || input == "back";
                                                                       });
            if (new_discount_type.empty() || new_discount_type == "back") return;
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "discount_type",
                                                                                                              new_discount_type)))));
        } else if (option == "6") {
            std::string new_discount =
                CaptureInputWithValidation("User managment", "Enter new user's discount:", ValidatePrice);
            if (new_discount.empty() || new_discount == "back") return;
            double new_discount_double = std::stod(new_discount);
            if (new_discount_double > 1) {
                PrintErrorMessage("The discount cannot be greater than 1.", "Try again.");
                return;
            }
            collection.update_one(filter_view,
                                  bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$set",
                                                                                                      bsoncxx::builder::basic::make_document(
                                                                                                          bsoncxx::builder::basic::kvp(
                                                                                                              "discount",
                                                                                                              new_discount_double)))));
        } else {
            PrintErrorMessage("Invalid selection.", "Try again.");
        }

        PrintSuccessMessage("User data has been updated successfully", "");
        DisplayManageUsersMenu();
        std::cin >> option;
    }
}

void Admin::AddLuggageItem(User &user) {
    std::string
        item_name = CaptureLineWithValidation("Adding an item", "Enter item name:", ValidateNonEmpty);
    if (item_name.empty() || item_name == "back") return;

    std::string
        item_description = CaptureLineWithValidation("Adding an item", "Enter item description:", ValidateNonEmpty);
    if (item_description.empty() || item_description == "back") return;

    std::string hints_str =
        CaptureLineWithValidation("Adding an item",
                                  "Provide important information (separated by a semicolon) (if missing: type \"none\")",
                                  ValidateNonEmpty);
    std::vector<std::string> hints;
    if (!hints_str.empty() && hints_str != "back" && hints_str != "none") {
        std::stringstream ss(hints_str);
        std::string hint;
        while (std::getline(ss, hint, ';')) {
            hints.push_back(hint);
        }
    }

    std::optional<bool> is_banned = CaptureBoolWithValidation("Adding an item",
                                                              "Is the item prohibited from air transportation? (yes/no):");
    if (!is_banned.has_value()) return;
    std::optional<bool> requires_approval =
        CaptureBoolWithValidation("Adding an item", "Does the item require carrier approval? (yes/no):");
    if (!requires_approval.has_value()) return;
    std::optional<bool> in_checked_luggage = CaptureBoolWithValidation("Adding an item",
                                                                       "Can the item be carried in registered baggage? (yes/no):");
    if (!in_checked_luggage.has_value()) return;
    std::optional<bool> in_hand_luggage = CaptureBoolWithValidation("Adding an item",
                                                                    "Can the item be carried in hand luggage? (yes/no):");
    if (!in_hand_luggage.has_value()) return;
    std::optional<bool> inform_pilot = CaptureBoolWithValidation("Adding an item",
                                                                 "Does the pilot need to be informed about carrying this item? (yes/no):");
    if (!inform_pilot.has_value()) return;

    std::string max_quantity_str =
        CaptureInputWithValidation("Adding an item", "Specify the maximum amount per person:", ValidatePrice);
    if (max_quantity_str.empty() || max_quantity_str == "back") return;
    int max_quantity = std::stoi(max_quantity_str);

    std::string avg_weight_str = CaptureInputWithValidation("Adding an item",
                                                            "Give the average weight of one object of this type:",
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

    PrintSuccessMessage("Item was added sucessfully", "");
}