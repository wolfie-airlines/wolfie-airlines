#include "../../User.h"
#include "../../../functions/info_print_functions.h"
#include "../user_prints/user_print_functions.h"
#include <iostream>

void User::setBlik(const std::string &payment) {

    if (paymentMethod == payment) {
        errorFunction("Wybrany sposób płatności jest już ustawiony.", "");
        return;
    }

    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", getPassword())
    );

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
                            bsoncxx::builder::basic::kvp("type", "blik")
                    ))
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    paymentMethod = payment;
    validFunction("Metoda płatności została pomyślnie zmieniona.", "");
}

void User::setVisa(const std::string &cardNumber, const std::string &cvv) {
    bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", email),
            bsoncxx::builder::basic::kvp("password", getPassword())
    );

    bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();
    mongocxx::cursor cursor_user = _collection.find(filter_view_email_password);
    if (cursor_user.begin() == cursor_user.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    // sprawdzenie czy taka karta już istnieje
    bsoncxx::document::value filter_builder_card_cvv = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("paymentMethod.cardNumber", cardNumber),
            bsoncxx::builder::basic::kvp("paymentMethod.cvv", cvv)
    );

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
                            bsoncxx::builder::basic::kvp("cvv", cvv)
                    ))
            ))
    );

    bsoncxx::document::view update_view = update_builder.view();
    _collection.update_one(filter_view_email_password, update_view);

    paymentMethod = "visa";
    validFunction("Metoda płatności została pomyślnie zmieniona.", "");
}

void handlePaymentOption(User& user) {
    int answer = CreateDefaultPaymentScreen();
    if (answer == 0) {
        // zmiana na VISĘ
        std::cout << "Podaj 3 ostatnie cyfry karty: ";
        std::string cardNumber;
        std::cin >> cardNumber;
        std::cout << "Podaj kod CVV karty: ";
        std::string cvv;
        std::cin >> cvv;
        if(user.paymentMethod == "visa") {
            errorFunction("Wybrany sposób płatności jest już ustawiony.", "");
            return;
        }
        user.setVisa(cardNumber, cvv);
    } else if (answer == 1) {
        user.setBlik("blik");
    } else if(answer == 2 ) {
        return;
    } else {
        errorFunction("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
}

bool paymentAuth(User& user, const std::string& paymentMethod, const std::string& titleMessage, int targetPrice) {
    std::string price = std::to_string(targetPrice);
    if(paymentMethod == "blik") {
        auto createBlikScreen = [&] {
            auto summary = ftxui::vbox({
                                               ftxui::hbox({ftxui::paragraphAlignCenter(titleMessage)}) | color(ftxui::Color::GrayDark),
                                               ftxui::separator(),
                                               ftxui::hbox({ftxui::paragraphAlignRight("Do zapłaty: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                                               ftxui::separator(),
                                               ftxui::hbox({
                                                                   ftxui::text(L"Podaj 6 cyfrowy kod BLIK poniżej:") | ftxui::bold | color(ftxui::Color::Green)
                                               }),
                                               ftxui::separator(),
                                               ftxui::hbox({
                                                            ftxui::text(L"quit. Anulowanie płatności") | ftxui::bold | color(ftxui::Color::RedLight)

                                               })
                                       });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createBlikScreen()));
        ftxui::Render(userScreen, *createBlikScreen());
        std::cout << userScreen.ToString() << '\0' << std::endl;

        int blikCode;
        std::cin >> blikCode;

        if(std::to_string(blikCode) == "quit") {
            errorFunction("Płatność została anulowana.", "");
            return false;
        }

        if (std::to_string(blikCode).length() != 6) {
            errorFunction("Kod BLIK musi składać się z 6 cyfr.", "Spróbuj ponownie.");
            return false;
        }

        if (blikCode == 123456) {
            errorFunction("Kod BLIK jest nieprawidłowy.", "Spróbuj ponownie.");
            return false;
        }

        bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("email", user.email),
                bsoncxx::builder::basic::kvp("password", user.getPassword())
        );

        bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

        mongocxx::cursor cursor_user = user.getCollection().find(filter_view_email_password);

        if (cursor_user.begin() == cursor_user.end()) {
            errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
            return false;
        }

        bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                        bsoncxx::builder::basic::kvp("moneySpent", user.moneySpent + targetPrice)
                ))
        );

        bsoncxx::document::view update_view = update_builder.view();
        user.getCollection().update_one(filter_view_email_password, update_view);

        user.moneySpent += targetPrice;
        validFunction("Płatność została zaakceptowana! Dziękujemy!", "");
        return true;
    } else if(paymentMethod == "visa") {
        auto createVisaDigitScreen = [&] {
            auto summary = ftxui::vbox({
                                               ftxui::hbox({ftxui::paragraphAlignCenter(titleMessage)}) | color(ftxui::Color::GrayDark),
                                               ftxui::separator(),
                                               ftxui::hbox({ftxui::paragraphAlignRight("Do zapłaty: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                                               ftxui::separator(),
                                               ftxui::hbox({
                                                                   ftxui::text(L"Podaj 3 ostatnie cyfry karty: ") | ftxui::bold | color(ftxui::Color::Green)
                                               }),
                                               ftxui::separator(),
                                                  ftxui::hbox({
                                                                ftxui::text(L"quit. Anulowanie płatności") | ftxui::bold | color(ftxui::Color::RedLight)

                                                  })
                                       });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createVisaDigitScreen()));
        ftxui::Render(userScreen, *createVisaDigitScreen());
        std::cout << userScreen.ToString() << '\0' << std::endl;

        std::string cardNumber;
        std::cin >> cardNumber;

        if(cardNumber == "quit") {
            errorFunction("Płatność została anulowana.", "");
            return false;
        }

        if (cardNumber.length() != 3) {
            errorFunction("Numer karty musi składać się z 3 cyfr.", "Spróbuj ponownie.");
            return false;
        }

        auto createVisaCVVScreen = [&] {
            auto summary = ftxui::vbox({
                                               ftxui::hbox({ftxui::paragraphAlignCenter(titleMessage)}) | color(ftxui::Color::GrayDark),
                                               ftxui::separator(),
                                               ftxui::hbox({ftxui::paragraphAlignRight("Do zapłaty: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                                               ftxui::separator(),
                                               ftxui::hbox({
                                                                   ftxui::text(L"Podaj 3 cyfrowy kod CVV karty: ") | ftxui::bold | color(ftxui::Color::Green)}),
                                       });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto cvvScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createVisaCVVScreen()));
        ftxui::Render(cvvScreen, *createVisaCVVScreen());
        std::cout << cvvScreen.ToString() << '\0' << std::endl;

        std::string cvv;
        std::cin >> cvv;

        if (cvv.length() != 3) {
            errorFunction("Kod CVV musi składać się z 3 cyfr.", "Spróbuj ponownie.");
            return false;
        }

        bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("email", user.email),
                bsoncxx::builder::basic::kvp("password", user.getPassword()),
                bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
                        bsoncxx::builder::basic::kvp("type", paymentMethod),
                        bsoncxx::builder::basic::kvp("cardNumber", cardNumber),
                        bsoncxx::builder::basic::kvp("cvv", cvv)
                ))
        );

        bsoncxx::document::view filter_view = filter_builder.view();

        mongocxx::cursor cursor_user = user.getCollection().find(filter_view);

        if (cursor_user.begin() == cursor_user.end()) {
            errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
            return false;
        }

        bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                        bsoncxx::builder::basic::kvp("moneySpent", user.moneySpent + targetPrice)
                )));
        bsoncxx::document::view update_view = update_builder.view();
        user.getCollection().update_one(filter_view, update_view);

        user.moneySpent += targetPrice;
        validFunction("Płatność została zaakceptowana! Dziękujemy!", "");
        return true;
    } else {
        errorFunction("Nieprawidłowy sposób płatności.", "Spróbuj ponownie.");
        return false;
    }
}
