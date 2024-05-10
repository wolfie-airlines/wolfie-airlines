#include "premium_cards_prints.h"

#include <iostream>

#include "../../../functions/helpers.h"
#include "../../user_functions/user_payments/user_payment_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"

std::string DisplayPremiumCardInfo() {
    auto summary = [&] {
        auto table = ftxui::Table({
            {"CARD", "BENEFIT", "PRICE"},
            {"Grey", "Free hand luggage", "100zł / month"},
            {"BLue", "5% discounts on each flight + previous benefit", "200zł / month"},
            {"Gold", "Choice of seat on the plane + previous benefits",
             "350zł / month"},
            {"Platinum", "15% discounts on every flight + previous benefits", "450zł / month"},
        });

        table.SelectAll().Border(ftxui::LIGHT);

        // Obramowania do każdej kolumny (oddzielenie)
        table.SelectColumn(0).Border(ftxui::LIGHT);
        table.SelectColumn(1).Border(ftxui::LIGHT);
        table.SelectColumn(2).Border(ftxui::LIGHT);

        // Pierwszy rząd na grubo, żeby było widać, że to nagłówek
        table.SelectRow(0).Decorate(ftxui::bold);
        table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
        table.SelectRow(0).Border(ftxui::LIGHT);

        for (int i = 2; i < 5; i++) {
            table.SelectRow(i).Border(ftxui::LIGHT);
        }

        // Margin kolumn
        table.SelectColumn(2).DecorateCells(ftxui::align_right);
        table.SelectColumn(1).DecorateCells(ftxui::center);

        std::vector<ftxui::Color> colors = {
            ftxui::Color::GrayLight,
            ftxui::Color::SkyBlue1,
            ftxui::Color::Gold1,
            ftxui::Color::LightSteelBlue1};

        // Ustawianie kolorów kart
        SetCellColor(table, 0, 1, colors[0]);
        SetCellColor(table, 0, 2, colors[1]);
        SetCellColor(table, 0, 3, colors[2]);
        SetCellColor(table, 0, 4, colors[3]);

        // Ustawianie kolorów benefitów
        SetCellColor(table, 1, 1, colors[0]);
        SetCellColor(table, 1, 2, colors[1]);
        SetCellColor(table, 1, 3, colors[2]);
        SetCellColor(table, 1, 4, colors[3]);

        // Ustawianie kolorów cen
        SetCellColor(table, 2, 1, colors[0]);
        SetCellColor(table, 2, 2, colors[1]);
        SetCellColor(table, 2, 3, colors[2]);
        SetCellColor(table, 2, 4, colors[3]);

        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L"CARD INFORMATION") | ftxui::bold}) | color(ftxui::Color::Orange3),
            ftxui::hbox({ftxui::text(L"Each premium card is entitled to specific discounts.") | ftxui::bold}) | color(ftxui::Color::Orange4),
            ftxui::hbox({ftxui::text(
                             L"There is a maximum of one discount per user (either card or discount).") |
                         ftxui::bold}) |
                color(ftxui::Color::Orange4),
            ftxui::separator(),
            table.Render(),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Return to the main menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Enter the name of the card you would like to purchase:") | ftxui::bold}) | color(ftxui::Color::YellowLight),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 200);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    std::cout << screen.ToString() << '\0' << std::endl;

    std::string choice;
    std::cin >> choice;
    return choice;
}

bool ValidCardPayment(User &user, int price) {
    std::string payment_method = user.payment_method_;
    bool authenticate_payment = AuthenticatePayment(user, payment_method, "PREMIUM CARD PAYMENT", price);
    return authenticate_payment;
}