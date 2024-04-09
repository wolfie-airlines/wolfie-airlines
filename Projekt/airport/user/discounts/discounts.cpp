#include "discounts.h"
#include "../../functions/info_print_functions.h"
#include "discounts_prints/discounts_prints.h"

double User::getDiscount() const {
    return discount;
}

std::string User::recognizeDiscount() {
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
            bsoncxx::builder::basic::kvp("password", getPassword())
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

    mongocxx::cursor cursor_user = getCollection().find(filter_view_email_password);

    if (cursor_user.begin() == cursor_user.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("discountType", discType),
                    bsoncxx::builder::basic::kvp("discount", disc)
            ))
    );


    bsoncxx::document::view update_view = update_builder.view();
    getCollection().update_one(filter_view_email_password, update_view);
    User::discount = disc;
    User::discountType = discType;
    validFunction("Zniżka została przypisana do konta", "Możesz zobaczyć ją w profilu i już zacząć z niej korzystać!");
}

double getDiscount(std::string choice) {
    if(choice == "1") {
        // weteran
        return 0.05;
    } else if(choice == "2") {
        // karta inwalidzka
        return 0.4;
    } else if(choice == "3") {
        // emeryt
        return 0.45;
    } else if(choice == "4") {
        // student
        return 0.49;
    } else {
        return 1;
    }
}

void handleDiscountChoice(User& user, std::string choice) {
    bool valid = validDiscount(choice);
    if(valid) {

        user.setDiscount(getDiscount(choice), "ulga");
    } else {
        std::cout << "Nie udało się przypisać zniżki do konta." << std::endl;
        return;
    }
}

void handleDiscountCard(User& user) {
    std::string choice = displayDiscountInfo();
    if (choice == "back") {
        return;
    }
    handleDiscountChoice(user, choice);
}