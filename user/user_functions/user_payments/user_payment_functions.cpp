#include <iostream>

#include "../../../functions/info_prints/info_prints.h"
#include "../../../functions/main_prints/main_prints.h"
#include "../user_prints/user_prints.h"

void HandlePaymentOption(User &user) {
    int answer = DisplayDefaultPaymentScreen();
    if (answer == 0) {
        // zmiana na VISĘ
        if (user.payment_method_ == "visa") {
            PrintErrorMessage("The selected payment method is already set.", "");
            return;
        }

        std::string
            card_number = DisplayMessageAndCaptureStringInput("CHANGE OF PAYMENT METHOD", "Enter the last 3 digits of the card: ");
        std::string
            cvv = DisplayMessageAndCaptureStringInput("CHANGE OF PAYMENT METHOD", "Enter the 3-digit CVV code of the card: ");

        user.SetVisa(card_number, cvv);
    } else if (answer == 1) {
        user.SetBlik("blik");
    } else if (answer == 2) {
        return;
    } else {
        PrintErrorMessage("Incorrect choice.", "Try again.");
    }
}

bool AuthenticatePayment(User &user, const std::string &payment_method, const std::string &title_message, int target_price) {
    std::string price = std::to_string(target_price);
    if (payment_method == "blik") {
        auto createBlikScreen = [&] {
            auto summary =
                ftxui::vbox({ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::GrayDark),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::paragraphAlignRight("To pay: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::text(L"Enter the 6-digit BLIK code below:") | ftxui::bold | color(ftxui::Color::Green)}),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::text(L"quit. Cancel payment") | ftxui::bold | color(ftxui::Color::RedLight)

                             })});
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createBlikScreen()));
        ftxui::Render(screen, *createBlikScreen());
        std::cout << screen.ToString() << '\0' << std::endl;

        std::string blik_code;
        std::cin >> blik_code;

        if (blik_code == "quit") {
            PrintErrorMessage("The payment was canceled.", "");
            return false;
        }

        if (blik_code.length() != 6) {
            PrintErrorMessage("The BLIK code must consist of 6 digits.", "Try again.");
            return false;
        }

        if (blik_code == "123456") {
            PrintErrorMessage("BLIK code is invalid.", "Try again.");
            return false;
        }

        bsoncxx::document::value filter_builder_email_password = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", user.email_),
            bsoncxx::builder::basic::kvp("password", user.GetPassword()));

        bsoncxx::document::view filter_view_email_password = filter_builder_email_password.view();

        mongocxx::cursor cursor_user = user.GetCollection().find(filter_view_email_password);

        if (cursor_user.begin() == cursor_user.end()) {
            PrintErrorMessage("The user could not be found in the database.", "");
            return false;
        }

        bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                                                     bsoncxx::builder::basic::kvp("moneySpent", user.money_spent_ + target_price))));

        bsoncxx::document::view update_view = update_builder.view();
        user.GetCollection().update_one(filter_view_email_password, update_view);

        user.money_spent_ += target_price;
        PrintSuccessMessage("The payment has been accepted! Thank you!", "");
        return true;
    } else if (payment_method == "visa") {
        auto visa_digit_screen = [&] {
            auto summary =
                ftxui::vbox({ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::GrayDark),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::paragraphAlignRight("To pay: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::text(L"Enter the last 3 digits of the card: ") | ftxui::bold | color(ftxui::Color::Green)}),
                             ftxui::separator(),
                             ftxui::hbox({ftxui::text(L"quit. Cancel payment") | ftxui::bold | color(ftxui::Color::RedLight)

                             })});
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*visa_digit_screen()));
        ftxui::Render(screen, *visa_digit_screen());
        std::cout << screen.ToString() << '\0' << std::endl;

        std::string card_number;
        std::cin >> card_number;

        if (card_number == "quit") {
            PrintErrorMessage("The payment was canceled.", "");
            return false;
        }

        if (card_number.length() != 3) {
            PrintErrorMessage("The card number must consist of 3 digits.", "Try again.");
            return false;
        }

        auto visa_cvv_screen = [&] {
            auto summary = ftxui::vbox({
                ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::GrayDark),
                ftxui::separator(),
                ftxui::hbox({ftxui::paragraphAlignRight("To pay: " + price + "zł")}) | color(ftxui::Color::LightSteelBlue),
                ftxui::separator(),
                ftxui::hbox({ftxui::text(L"Enter the 3-digit CVV code of the card: ") | ftxui::bold | color(ftxui::Color::Green)}),
            });
            auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
            document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
            return std::make_shared<ftxui::Element>(document);
        };

        auto cvv_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*visa_cvv_screen()));
        ftxui::Render(cvv_screen, *visa_cvv_screen());
        std::cout << cvv_screen.ToString() << '\0' << std::endl;

        std::string cvv;
        std::cin >> cvv;

        if (cvv.length() != 3) {
            PrintErrorMessage("The CVV code must consist of 3 digits.", "Try again.");
            return false;
        }

        bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", user.email_),
            bsoncxx::builder::basic::kvp("password", user.GetPassword()),
            bsoncxx::builder::basic::kvp("paymentMethod", bsoncxx::builder::basic::make_document(
                                                              bsoncxx::builder::basic::kvp("type", payment_method),
                                                              bsoncxx::builder::basic::kvp("card_number", card_number),
                                                              bsoncxx::builder::basic::kvp("cvv", cvv))));

        bsoncxx::document::view filter_view = filter_builder.view();

        mongocxx::cursor cursor_user = user.GetCollection().find(filter_view);

        if (cursor_user.begin() == cursor_user.end()) {
            PrintErrorMessage("The user could not be found in the database.", "");
            return false;
        }

        bsoncxx::document::value update_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("$set", bsoncxx::builder::basic::make_document(
                                                     bsoncxx::builder::basic::kvp("moneySpent", user.money_spent_ + target_price))));
        bsoncxx::document::view update_view = update_builder.view();
        user.GetCollection().update_one(filter_view, update_view);

        user.money_spent_ += target_price;
        PrintSuccessMessage("The payment has been accepted! Thank you!", "");
        return true;
    } else {
        PrintErrorMessage("Incorrect payment method.", "Try again.");
        return false;
    }
}
