#include "luggage_prints.h"

#include "../../functions/info_prints/info_prints.h"
#include "../../functions/main_prints/main_prints.h"
#include "../../user/user_functions/user_payments/user_payment_functions.h"
#include "../item/item_handler.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"

const std::string AIRPORT_NAME = "WOLFI AIRPORT ️ ✈";
const std::string ITEM_CARD = "KARTA PRZEDMIOTU";

std::vector<ftxui::Component> CreateGroups(const std::vector<ftxui::Component> &checkbox_components) {
  std::vector<ftxui::Component> vertical_containers;
  for (size_t i = 0; i < checkbox_components.size(); i += 8) {
    std::vector<ftxui::Component> group;
    for (size_t j = i; j < i + 8 && j < checkbox_components.size(); ++j) {
      group.push_back(checkbox_components[j]);
    }
    vertical_containers.push_back(ftxui::Container::Vertical(group));
  }
  return vertical_containers;
}

void PrintSpecificItem(Item &item) {
  std::string
      description = item.GetDescription().empty() ? "Brak szczegółowego opisu przedmiotu" : item.GetDescription();

  std::stringstream stream;
  stream << std::fixed << std::setprecision(3) << item.GetWeight();
  std::string weight = stream.str();

  std::vector<ftxui::Element> elements;
  std::vector<std::string> hints = item.GetHints();

  if (!hints.empty()) {
    std::vector<ftxui::Element> hint_elements;
    for (const auto &hint : hints) {
      std::string hint_with_bullet = "• " + hint;
      hint_elements.push_back(ftxui::paragraph(hint_with_bullet) | ftxui::color(ftxui::Color::White));
    }

    auto hint_box = ftxui::vbox(std::move(hint_elements));

    elements.push_back(ftxui::hbox({ftxui::text("Ważne informacje: ") | ftxui::bold
                                        | ftxui::color(ftxui::Color::DarkSeaGreen2),
                                    hint_box}));
  }

  const std::string &profession = item.GetProfession();
  ftxui::Element profession_element = ftxui::hbox({});
  if (!profession.empty()) {
    profession_element = ftxui::hbox({ftxui::text("Dostępny w każdej ilości dla zawodu: ") | ftxui::bold
                                         | ftxui::color(ftxui::Color::Gold1),
                                      ftxui::text(profession) | ftxui::color(ftxui::Color::White)});
  }

  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(ITEM_CARD) | ftxui::bold})
                                       | color(ftxui::Color::Orange3),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::paragraphAlignCenter(item.GetItemName()) | ftxui::bold})
                                       | color(ftxui::Color::Orange1),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Przedmiot: ") | ftxui::bold
                                                    | color(ftxui::Color::SkyBlue1),
                                                ftxui::text(item.GetItemName()) | color(ftxui::Color::White)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Opis przedmiotu: ") | ftxui::bold
                                                    | color(ftxui::Color::DarkSeaGreen2),
                                                ftxui::paragraph(description) | color(ftxui::Color::White)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Zabroniony w transporcie lotniczym: ") | ftxui::bold
                                                    | color(ftxui::Color::RedLight),
                                                ftxui::text(item.IsForbidden() ? "TAK" : "NIE") | color(
                                                    item.IsForbidden() ? ftxui::Color::RedLight
                                                                       : ftxui::Color::GreenLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Przewóz w bagażu rejestrowanym: ") | ftxui::bold
                                                    | color(ftxui::Color::Aquamarine1),
                                                ftxui::text(item.IsRegisteredLuggage() ? "✅" : "❌")}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Przewóz w bagażu podręcznym: ") | ftxui::bold
                                                    | color(ftxui::Color::MediumOrchid3),
                                                ftxui::text(item.IsHandLuggage() ? "✅" : "❌")}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Wymagana zgoda pilota: ") | ftxui::bold
                                                    | color(ftxui::Color::LightSkyBlue1),
                                                ftxui::text(item.IsPilotAllowance() ? "✅" : "❌")}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Maksymalna ilość (sztuk): ") | ftxui::bold
                                                    | color(ftxui::Color::LightCoral),
                                                ftxui::text(std::to_string((int) item.GetMaxCount()))
                                                    | color(ftxui::Color::Salmon1)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Waga (jednej sztuki przedmiotu, wyznaczana na oko): ")
                                                    | ftxui::bold | color(ftxui::Color::SandyBrown),
                                                ftxui::text(weight + " kg") | color(ftxui::Color::LightPink1)}),
                                   ftxui::separator(),
                                   elements.empty() ? ftxui::hbox({}) : ftxui::hbox(elements),
                                   ftxui::separator(),
                                   profession_element,
                               });

    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen =
      ftxui::Screen::Create(ftxui::Dimension::Fit(*create_screen()), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;
}

void PrintAllItems(User &user) {
  int page = 0;
  auto collection = user.GetSpecificCollection("luggage_list");
  auto cursor = collection.find({});
  std::vector<bsoncxx::document::view> documents;
  for (auto &&doc : cursor) {
    documents.push_back(doc);
  }

  std::vector<Item> items = GetItems(user);
  int total_pages = (items.size() + 7) / 8;

  while (true) {
    std::vector<std::vector<std::string>> rows;
    for (int i = page * 8; i < (page + 1) * 8 && i < items.size(); i++) {
      const auto &item = items[i];
      std::string is_forbidden_string = item.IsForbidden() ? "TAK" : "NIE";
      std::string is_registered_luggage_string = item.IsRegisteredLuggage() ? "✅" : "❌";
      std::string is_hand_luggage_string = item.IsHandLuggage() ? "✅" : "❌";
      std::string is_pilot_allowance_string = item.IsPilotAllowance() ? "✅" : "❌";
      rows.push_back({std::to_string(i + 1),
                      item.GetItemName(),
                      is_forbidden_string,
                      is_registered_luggage_string,
                      is_hand_luggage_string,
                      is_pilot_allowance_string});
    }

    std::vector<std::string> header = {"NUMER", "PRZEDMIOT", "ZABRONIONY", "BAGAŻ REJESTROWANY", "BAGAŻ PODRĘCZNY",
                                       "WYMAGA ZGODY PILOTA"};
    rows.insert(rows.begin(), header);

    auto table = ftxui::Table(rows);
    table.SelectAll().Border(ftxui::LIGHT);

    // Pierwszy rząd na grubo, żeby było widać, że to nagłówek
    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
    table.SelectRow(0).Border(ftxui::LIGHT);

    // Margin kolumn
    table.SelectColumns(0, 5).DecorateCells(ftxui::center);

    // Kolory numerów
    table.SelectColumn(0).DecorateCells(ftxui::color(ftxui::Color::DarkOliveGreen3));

    // Kolory przedmiotów
    table.SelectColumn(1).DecorateCells(ftxui::color(ftxui::Color::SkyBlue1));

    // Kolory zabronionych przedmiotów
    for (int i = 0; i < rows.size(); i++) {
      if (rows[i][2] == "TAK") {
        table.SelectCell(2, i).DecorateCells(ftxui::color(ftxui::Color::RedLight));
      } else {
        table.SelectCell(2, i).DecorateCells(ftxui::color(ftxui::Color::White));
      }
    }

    // Kolory bagażu rejestrowanego
    table.SelectColumn(3).DecorateCells(ftxui::color(ftxui::Color::Aquamarine1));

    // Kolory bagażu podręcznego
    table.SelectColumn(4).DecorateCells(ftxui::color(ftxui::Color::MediumOrchid3));

    // Kolory zgody pilota
    table.SelectColumn(5).DecorateCells(ftxui::color(ftxui::Color::LightSkyBlue1));

    // Oddziałka między wierszami
    for (int i = 2; i < 9; i++) {
      table.SelectRow(i).Border(ftxui::LIGHT);
    }

    // Oddziałka między kolumnami
    for (int i = 1; i < 6; i++) {
      table.SelectColumn(i).Border(ftxui::LIGHT);
    }

    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter("LISTA WSZYSTKICH PRZEDMIOTÓW")}) |
                                       color(ftxui::Color::GrayDark),
                                   table.Render(),
                                   ftxui::hbox({
                                                   ftxui::paragraphAlignRight("Strona " + std::to_string(page + 1) + "/"
                                                                                  + std::to_string(total_pages))
                                                       | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
                                               }),
                                   ftxui::vbox({
                                                   ftxui::separator(),
                                                   ftxui::hbox({
                                                                   ftxui::text("🧭 NAWIGACJA")
                                                                       | ftxui::color(ftxui::Color::YellowLight)
                                                                       | ftxui::bold,
                                                               }),
                                                   ftxui::separator(),
                                                   ftxui::hbox({
                                                                   ftxui::text("next. Następna strona")
                                                                       | ftxui::color(ftxui::Color::CadetBlue)
                                                                       | ftxui::bold,
                                                               }),
                                                   ftxui::hbox({
                                                                   ftxui::text("prev. Poprzednia strona")
                                                                       | ftxui::color(ftxui::Color::DarkOliveGreen2)
                                                                       | ftxui::bold,
                                                               }),
                                                   ftxui::hbox({ftxui::text("quit. \U0001f51a  Wyjdź z listy")
                                                                    | ftxui::color(ftxui::Color::RedLight)
                                                                    | ftxui::bold}),
                                                   ftxui::separator(),
                                                   ftxui::hbox({
                                                                   ftxui::text(
                                                                       "Wybierz numer przedmiotu, aby zobaczyć wyświetlić jego szczegóły")
                                                                       | ftxui::color(ftxui::Color::YellowLight)
                                                                       | ftxui::bold,
                                                               }),
                                               }),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});

    PrintNodeScreen(document);

    std::string response;
    std::cin >> response;
    if (response == "next") {
      if (page == total_pages - 1) {
        continue;
      }
      page++;
    } else if (response == "prev") {
      if (page == 0) {
        continue;
      }
      page--;
    } else if (response == "quit") {
      return;
    } else {
      try {
        int item_number = std::stoi(response);
        if (item_number >= 1 && item_number <= 34) {
          int index = item_number - 1;
          if (index < items.size()) {
            PrintSpecificItem(items[index]);
          }
        } else {
          PrintErrorMessage("Nie ma takiego przedmiotu!", "Wybierz poprawny numer");
          continue;
        }
      } catch (std::invalid_argument &e) {
        continue;
      }
    }
  }
}
