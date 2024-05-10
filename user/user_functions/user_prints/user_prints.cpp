#include "user_prints.h"

#include <iostream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

std::string DisplaySettingsMenu(const User &user) {
    auto settings_screen = [&] {
        auto summary = ftxui::vbox({
            ftxui::hbox({ftxui::text(L" ACCOUNT SETTINGS") | ftxui::bold}) | color(ftxui::Color::Blue),
            ftxui::hbox({ftxui::paragraphAlignRight("Logged as:")}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::paragraphAlignRight(user.username_)}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"1. Change username   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"2. Change e-mail adress   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"3. Change password   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"4. Verify your profession   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"5. Change the default payment method   ") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"back. \U0001F519 Return to main menu   ") | ftxui::bold}) | color(ftxui::Color::CadetBlue),
            // ---------
            ftxui::separator(),
            ftxui::hbox({ftxui::text(
                             L"Enter the action (or its number) you want to perform below:") |
                         ftxui::bold}) |
                color(ftxui::Color::YellowLight),
        });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*settings_screen()));
    ftxui::Render(screen, *settings_screen());
    std::cout << screen.ToString() << '\0' << std::endl;

    std::string option;
    std::cin >> option;
    return option;
}

int DisplayDefaultPaymentScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> entries = {
        "Change the default payment method to VISA card",
        "Change the default payment method to BLIK",
        "\U0001F519 Return to main menu",
    };
    int selected = 0;

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

void DisplayProfileScreen(User &user) {
    std::string username = user.username_;
    std::transform(username.begin(), username.end(), username.begin(), ::toupper);

    std::string profession = user.profession_;
    profession[0] = std::toupper(profession[0]);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << user.money_spent_;
    std::string money_spent = oss.str();
    std::string ticket_bought = std::to_string(user.ticket_bought_);

    std::string premium_card = user.premium_card_;
    premium_card[0] = std::toupper(premium_card[0]);

    std::string payment_method = user.payment_method_;
    payment_method[0] = std::toupper(payment_method[0]);

    std::string discount = user.RecognizeDiscount();

    std::ostringstream oss2;
    oss2 << std::fixed << std::setprecision(2) << user.money_saved_;
    std::string money_saved = oss2.str();

    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(" USER PROFILE ") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                         ftxui::text(username) | ftxui::color(ftxui::Color::CadetBlue)}),
            ftxui::hbox({ftxui::text("")}),
            ftxui::hbox({ftxui::text("Occupation: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.profession_ == "none") ? ftxui::text("None") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(profession) | ftxui::color(ftxui::Color::Green)}),
            ftxui::hbox({ftxui::text("Premium card: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.premium_card_ == "none") ? ftxui::text("None") | ftxui::color(ftxui::Color::GrayDark) : (user.premium_card_ == "gold")   ? ftxui::text(premium_card) | ftxui::color(ftxui::Color::Gold1)
                                                                                                                   : (user.premium_card_ == "blue")     ? ftxui::text(premium_card) | ftxui::color(ftxui::Color::SkyBlue1)
                                                                                                                   : (user.premium_card_ == "grey")     ? ftxui::text(premium_card) | ftxui::color(ftxui::Color::GrayLight)
                                                                                                                   : (user.premium_card_ == "platinum") ? ftxui::text(premium_card) | ftxui::color(ftxui::Color::LightSteelBlue1)
                                                                                                                                                        : ftxui::text("None") | ftxui::color(ftxui::Color::GrayDark)}),
            ftxui::hbox({ftxui::text("Discount: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (discount == "none") ? ftxui::text("None") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(discount) | ftxui::color(ftxui::Color::SkyBlue2)}),
            ftxui::hbox({ftxui::text("Money saved with a discount / premium card: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         (user.money_saved_ == 0) ? ftxui::text("0") | ftxui::color(ftxui::Color::GrayDark) : ftxui::text(money_saved + "zł") | ftxui::color(ftxui::Color::Gold1)}),
            ftxui::hbox({ftxui::text("Date of account creation: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(user.registration_date_) | ftxui::color(ftxui::Color::SteelBlue)}),
            ftxui::hbox({ftxui::text("Default payment method: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(payment_method) | ftxui::color(ftxui::Color::Gold1)}),
            ftxui::hbox({ftxui::text("Number of tickets purchased: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(ticket_bought) | ftxui::color(ftxui::Color::Violet)}),
            ftxui::hbox({// U0001F4B8 -> 💸
                         ftxui::text(L"\U0001F4B8 spent in WOLFIE AIRLINES: ") | ftxui::color(ftxui::Color::GrayLight) | ftxui::bold,
                         ftxui::text(money_spent + "zł") | ftxui::color(ftxui::Color::SandyBrown)}),
            // ---------
            ftxui::separator(),
            ftxui::hbox({// U0001F519 -> 🔙
                         ftxui::text(L"back. \U0001F519  Return to the main menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(
                             L"Thank you for choosing WOLFIE AIRLINES and for being with us 🙏") |
                         ftxui::color(ftxui::Color::YellowLight) | ftxui::bold}),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(),
                                        ftxui::Dimension::Fit(*std::make_shared<ftxui::Element>(document)));

    ftxui::Render(screen, *std::make_shared<ftxui::Element>(document));

    std::cout << screen.ToString() << '\0' << std::endl;

    std::string back_option;
    std::cin >> back_option;
    if (back_option == "back") {
        return;
    }
}