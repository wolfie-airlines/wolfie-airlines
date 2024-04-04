#include "../../User.h"
#include "../../../functions/info_print_functions.h"

void User::setPaymentMethod(const std::string &payment) {

    if (paymentMethod == payment) {
        errorFunction("Wybrany sposób płatności jest już ustawiony.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

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
    if (password != repeatedPassword) {
        errorFunction("Podane hasła nie są takie same.", "Spróbuj ponownie.");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
                            bsoncxx::builder::basic::kvp("type", "blik")
                    ))
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    paymentMethod = payment;
    validFunction("Metoda płatności została pomyślnie zmieniona.", "");
}

void User::handleVisa(const std::string &cardNumber, const std::string &cvv) {
    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", password)
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        std::cout << email << " " << password << std::endl;
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                    bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
                            bsoncxx::builder::basic::kvp("type", "visa"),
                            bsoncxx::builder::basic::kvp("cardNumber", cardNumber),
                            bsoncxx::builder::basic::kvp("cvv", cvv)
                    ))
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    paymentMethod = "visa";
}

