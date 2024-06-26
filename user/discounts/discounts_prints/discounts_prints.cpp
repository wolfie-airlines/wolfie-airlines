#include "discounts_prints.h"

#include <iostream>

#include "../../user_functions/user_payments/user_payment_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"
#include "../../../functions/helpers.h"

std::string DisplayDiscountInfo() {
  auto summary = [&] {
    auto table = ftxui::Table({
                                  {"Numer ulgi", "TYP ULGI", "WYMAGANIA WERYFIKACJI", "ZNIŻKA DLA ULGI"},
                                  {"1.", "Weteran wojenny", "Legitymacja weterana", "95% zniżki"},
                                  {"2.", "Karta inwalidzka", "Karta inwalidzka", "60% zniżki"},
                                  {"3.", "Emeryt", "Legitymacja emeryta", "55% zniżki"},
                                  {"4.", "Student", "Legitymacja studencka", "51% zniżki"},
                              });

    table.SelectAll().Border(ftxui::LIGHT);

    // Obramowania do każdej kolumny (oddzielenie)
    table.SelectColumn(0).Border(ftxui::LIGHT);
    table.SelectColumn(1).Border(ftxui::LIGHT);
    table.SelectColumn(2).Border(ftxui::LIGHT);
    table.SelectColumn(3).Border(ftxui::LIGHT);

    // Pierwszy rząd na grubo, żeby było widać, że to nagłówek
    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
    table.SelectRow(0).Border(ftxui::LIGHT);

    for (int i = 2; i < 5; i++) {
      table.SelectRow(i).Border(ftxui::LIGHT);
    }

    // Margin kolumn
    table.SelectColumn(1).DecorateCells(ftxui::center);
    table.SelectColumn(2).DecorateCells(ftxui::center);
    table.SelectColumn(3).DecorateCells(ftxui::align_right);

    std::vector<ftxui::Color> colors = {
        ftxui::Color::GrayLight,
        ftxui::Color::SkyBlue1,
        ftxui::Color::Gold1,
        ftxui::Color::LightSteelBlue1
    };

    // Ustawianie kolorów kart
    SetCellColor(table, 1, 1, ftxui::Color::GrayLight);
    SetCellColor(table, 1, 2, ftxui::Color::SkyBlue1);
    SetCellColor(table, 1, 3, ftxui::Color::Gold1);
    SetCellColor(table, 1, 4, ftxui::Color::LightSteelBlue1);

    // Ustawianie kolorów benefitów
    SetCellColor(table, 2, 1, ftxui::Color::GrayLight);
    SetCellColor(table, 2, 2, ftxui::Color::SkyBlue1);
    SetCellColor(table, 2, 3, ftxui::Color::Gold1);
    SetCellColor(table, 2, 4, ftxui::Color::LightSteelBlue1);

    // Ustawianie kolorów cen
    SetCellColor(table, 3, 1, ftxui::Color::GrayLight);
    SetCellColor(table, 3, 2, ftxui::Color::SkyBlue1);
    SetCellColor(table, 3, 3, ftxui::Color::Gold1);
    SetCellColor(table, 3, 4, ftxui::Color::LightSteelBlue1);

    auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"INFORMACJE O KARTACH") | ftxui::bold})
                                       | color(ftxui::Color::Orange3),
                                   ftxui::hbox({ftxui::text(L"Każdej uldze przysługują konkretne zniżki.")
                                                    | ftxui::bold}) | color(ftxui::Color::Orange4),
                                   ftxui::hbox({ftxui::text(
                                       L"Przysługuje maksymalnie jedna zniżka na użytkownika (albo karta albo ulga).")
                                                    | ftxui::bold}) | color(ftxui::Color::Orange4),
                                   ftxui::separator(),
                                   table.Render(),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do głównego menu.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"Wpisz numer ulgi, o którą chciałbyś się starać:")
                                                    | ftxui::bold}) | color(ftxui::Color::YellowLight),
                               });
    return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
  };

  auto document = ftxui::vbox({summary()});

  document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 200);

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
  ftxui::Render(user_screen, document);
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string choice;
  std::cin >> choice;
  return choice;
}

bool ValidDiscount(const std::string &discount_choice) {
  std::string discount_text;
  if (discount_choice == "1") {
    discount_text = "Podaj 3 ostatnie cyfry swojej legitymacji weterana: ";
  } else if (discount_choice == "2") {
    discount_text = "Podaj 3 ostatnie cyfry swojej karty inwalidzkiej: ";
  } else if (discount_choice == "3") {
    discount_text = "Podaj 3 ostatnie cyfry swojej legitymacji emeryta: ";
  } else if (discount_choice == "4") {
    discount_text = "Podaj 3 ostatnie cyfry swojej legitymacji studenckiej: ";
  } else {
    std::cout << "Nieprawidłowy wybór." << std::endl;
    return false;
  }

  auto discount_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter("WERYFIKACJA ZNIŻKI")})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(discount_text) | ftxui::bold | color(ftxui::Color::Green)}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*discount_screen()));
  ftxui::Render(screen, *discount_screen());
  std::cout << screen.ToString() << '\0' << std::endl;

  std::string discount_code;
  std::cin >> discount_code;

  if (discount_code == "123") {
    return false;
  }

  if (discount_code.length() != 3 || !std::all_of(discount_code.begin(), discount_code.end(), ::isdigit)) {
    return false;
  }

  return true;
}