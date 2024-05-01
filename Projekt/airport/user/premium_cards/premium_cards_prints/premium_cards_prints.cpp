#include "premium_cards_prints.h"

#include <iostream>

#include "../../user_functions/user_payments/user_payment_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"

std::string displayPremiumCardInfo() {
    auto summary = [&] {
        auto table = ftxui::Table({
            {"KARTA", "BENEFIT", "CENA"},
            {"Szara", "Darmowy bagaż podręczny", "100zł / miesiąc"},
            {"Niebieska", "5% zniżki na każdy lot + poprzedni benefit", "200zł / miesiąc"},
            {"Złota", "Możliwość wyboru miejsca w samolocie + poprzednie benefity", "350zł / miesiąc"},
            {"Platynowa", "15% zniżki na każdy lot + poprzednie benefity", "450zł / miesiąc"},
        });

        table.SelectAll().Border(ftxui::LIGHT);

        // Obramowania do każdej kolumny (oddzielenie)
        table.SelectColumn(0).Border(ftxui::LIGHT);
        table.SelectColumn(1).Border(ftxui::LIGHT);
        table.SelectColumn(2).Border(ftxui::LIGHT);

        // Pierwszy rząd na grubo żeby było widać że to nagłówek
        table.SelectRow(0).Decorate(ftxui::bold);
        table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
        table.SelectRow(0).Border(ftxui::LIGHT);

        for (int i = 2; i < 5; i++) {
            table.SelectRow(i).Border(ftxui::LIGHT);
        }

        // Margin kolumn
        table.SelectColumn(2).DecorateCells(ftxui::align_right);
        table.SelectColumn(1).DecorateCells(ftxui::center);

        // Ustawianie kolorów kart
        // TODO: Zrobić to jakoś ładniej
        table.SelectCell(0, 1).DecorateCells(ftxui::color(ftxui::Color::GrayLight));
        table.SelectCell(0, 2).DecorateCells(ftxui::color(ftxui::Color::SkyBlue1));
        table.SelectCell(0, 3).DecorateCells(ftxui::color(ftxui::Color::Gold1));
        table.SelectCell(0, 4).DecorateCells(ftxui::color(ftxui::Color::LightSteelBlue1));

        // Ustawianie kolorów benefitów
        table.SelectCell(1, 1).DecorateCells(ftxui::color(ftxui::Color::GrayLight));
        table.SelectCell(1, 2).DecorateCells(ftxui::color(ftxui::Color::SkyBlue1));
        table.SelectCell(1, 3).DecorateCells(ftxui::color(ftxui::Color::Gold1));
        table.SelectCell(1, 4).DecorateCells(ftxui::color(ftxui::Color::LightSteelBlue1));

        // Ustawianie kolorów cen
        table.SelectCell(2, 1).DecorateCells(ftxui::color(ftxui::Color::GrayLight));
        table.SelectCell(2, 2).DecorateCells(ftxui::color(ftxui::Color::SkyBlue1));
        table.SelectCell(2, 3).DecorateCells(ftxui::color(ftxui::Color::Gold1));
        table.SelectCell(2, 4).DecorateCells(ftxui::color(ftxui::Color::LightSteelBlue1));

        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L"INFORMACJE O KARTACH") | ftxui::bold}) | color(ftxui::Color::Orange3),
            ftxui::hbox({ftxui::text(L"Każdej karcie premium przysługują konkretne zniżki.") | ftxui::bold}) | color(ftxui::Color::Orange4),
            ftxui::hbox({ftxui::text(L"Przysługuje maksymalnie jedna zniżka na użytkownika (albo karta albo ulga).") | ftxui::bold}) | color(ftxui::Color::Orange4),
            ftxui::separator(),
            table.Render(),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do głównego menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"Wpisz nazwę karty, którą chciałbyś zakupić:") | ftxui::bold}) | color(ftxui::Color::YellowLight),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 200);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string choice;
    std::cin >> choice;
    return choice;
}

bool validCardPayment(User& user, int price) {
    std::string paymentMethod = user.paymentMethod;
    bool validPayment = paymentAuth(user, paymentMethod, "PŁATNOŚĆ ZA KARTĘ PREMIUM", price);
    return validPayment;
}