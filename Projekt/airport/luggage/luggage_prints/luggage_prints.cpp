#include "luggage_prints.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/table.hpp"
#include "../item/ItemHandler.h"
#include "../../functions/info_print_functions.h"

void printSpecificItem(Item& item) {
    auto createScreen = [&] {
        std::string description = item.getDescription().empty() ? "Brak szczegółowego opisu przedmiotu" : item.getDescription();

        std::stringstream stream;
        stream << std::fixed << std::setprecision(3) << item.getWeight();
        std::string weight = stream.str();

        std::vector<ftxui::Element> elements;
        std::vector<std::string> hints = item.getHints();

        if (!hints.empty()) {
            std::vector<ftxui::Element> hintElements;
            for (const auto& hint : hints) {
                std::string hintWithBullet = "• " + hint;
                hintElements.push_back(ftxui::paragraph(hintWithBullet) | ftxui::color(ftxui::Color::White));
            }

            auto hintBox = ftxui::vbox(std::move(hintElements));

            elements.push_back(ftxui::hbox({
                                                   ftxui::text("Ważne informacje: ") | ftxui::bold | ftxui::color(ftxui::Color::DarkSeaGreen2),
                                                   hintBox
                                           }));
        }

        auto summary = ftxui::vbox({
                                           ftxui::hbox({
                                                               ftxui::paragraphAlignCenter("KARTA PRZEDMIOTU") | ftxui::bold
                                                       }) | color(ftxui::Color::Orange3),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::paragraphAlignCenter(item.getItemName()) | ftxui::bold
                                                       }) | color(ftxui::Color::Orange1),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Przedmiot: ") | ftxui::bold | color(ftxui::Color::SkyBlue1),
                                                               ftxui::text(item.getItemName()) | color(ftxui::Color::White)
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Opis przedmiotu: ") | ftxui::bold | color(ftxui::Color::DarkSeaGreen2),
                                                               ftxui::paragraph(description) | color(ftxui::Color::White)
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Zabroniony w transporcie lotniczym: ") | ftxui::bold | color(ftxui::Color::RedLight),
                                                               ftxui::text(item.isForbidden() ? "TAK" : "NIE") | color(
                                                                       item.isForbidden() ? ftxui::Color::RedLight : ftxui::Color::GreenLight)
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Przewóz w bagażu rejestrowanym: ") | ftxui::bold | color(ftxui::Color::Aquamarine1),
                                                               ftxui::text(item.isRegisteredLuggage() ? "✅" : "❌")
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Przewóz w bagażu podręcznym: ") | ftxui::bold | color(ftxui::Color::MediumOrchid3),
                                                               ftxui::text(item.isHandLuggage() ? "✅" : "❌")
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Wymagana zgoda pilota: ") | ftxui::bold | color(ftxui::Color::LightSkyBlue1),
                                                               ftxui::text(item.isPilotAllowance() ? "✅" : "❌")
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Maksymalna ilość (sztuk): ") | ftxui::bold | color(ftxui::Color::LightCoral),
                                                               ftxui::text(std::to_string((int) item.getMaxCount()))  | color(ftxui::Color::Salmon1)
                                                       }),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Waga (jednej sztuki przedmiotu, wyznaczana na oko): ") | ftxui::bold | color(ftxui::Color::SandyBrown),
                                                               ftxui::text(weight + " kg") | color(ftxui::Color::LightPink1)
                                                       }),
                                             ftxui::separator(),
                                             elements.empty() ? ftxui::separator() : ftxui::hbox(elements),
                                   });

        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*createScreen()), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;
}

void printAllItems(User& user) {
    int page = 0;
    auto collection = user.getSpecificCollection("luggage_list");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto &&doc: cursor) {
        documents.push_back(doc);
    }

    std::vector<Item> items = getItems(user);
    int totalPages = (items.size() + 4) / 5;

    while(true) {
        std::vector<std::vector<std::string>> rows;
        for (int i = page * 5; i < (page + 1) * 5 && i < items.size(); i++) {
            const auto &item = items[i];
            std::string isForbidden = item.isForbidden() ? "TAK" : "NIE";
            std::string isRegisteredLuggage = item.isRegisteredLuggage() ? "✅" : "❌";
            std::string isHandLuggage = item.isHandLuggage() ? "✅" : "❌";
            std::string isPilotAllowance = item.isPilotAllowance() ? "✅" : "❌";
            rows.push_back({
                                   std::to_string(i + 1),
                                   item.getItemName(),
                                   isForbidden,
                                   isRegisteredLuggage,
                                   isHandLuggage,
                                   isPilotAllowance
                           });
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
        for(int i = 2; i < 5; i++) {
            table.SelectRow(i).Border(ftxui::LIGHT);
        }

        // Oddziałka między kolumnami
        for(int i = 1; i < 6; i++) {
            table.SelectColumn(i).Border(ftxui::LIGHT);
        }


        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter("LISTA WSZYSTKICH PRZEDMIOTÓW")}) |
                                           color(ftxui::Color::GrayDark),
                                           table.Render(),
                                           ftxui::vbox({
                                               ftxui::separator(),
                                               ftxui::hbox({
                                                   ftxui::text("🧭 NAWIGACJA") | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
                                                   }),
                                                   ftxui::separator(),
                                               ftxui::hbox({
                                                   ftxui::text("next. Następna strona") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                                                   }),
                                               ftxui::hbox({
                                                   ftxui::text("prev. Poprzednia strona") | ftxui::color(ftxui::Color::DarkOliveGreen2) | ftxui::bold,
                                                   }),
                                               ftxui::hbox({
                                                    ftxui::text("quit. \U0001f51a  Wyjdź z listy") | ftxui::color(ftxui::Color::RedLight) | ftxui::bold
                                                    }),
                                                    ftxui::separator(),
                                               ftxui::hbox({
                                                   ftxui::text("Wybierz numer przedmiotu, aby zobaczyć wyświetlić jego szczegóły") | ftxui::color(ftxui::Color::YellowLight) | ftxui::bold,
                                                   }),
                                           }),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});

        auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
        ftxui::Render(screen, document);
        std::cout << screen.ToString() << '\0' << std::endl;

        std::string response;
        std::cin >> response;
        if (response == "next") {
            if(page == totalPages - 1) {
                continue;
            }
            page++;
        } else if (response == "prev") {
            if(page == 0) {
                continue;
            }
            page--;
        } else if (response == "quit") {
            return;
        } else {
            try {
                int itemNumber = std::stoi(response);
                if(itemNumber >= 1 && itemNumber <= 31) {
                    int index = itemNumber - 1;
                    if(index < items.size()) {
                        printSpecificItem(items[index]);
                    }
                } else {
                    errorFunction("Nie ma takiego przedmiotu!", "Wybierz poprawny numer");
                    continue;
                }
            } catch (std::invalid_argument &e) {
                continue;
            }
        }
    }
}

void welcomeInLuggageCheckin(User& user) {
    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter(user.username + ", witamy w odprawie bagażowej!")}) | color(ftxui::Color::GrayDark),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text("Przed rozpoczęciem masz możliwość wyświetlenia listy wszystkich dozwolonych i zabronionych rzeczy do wzięcia do bagażu. Chcesz to zrobić?") | ftxui::bold | color(ftxui::Color::Green)
                                           }),
                                             ftxui::separator(),
                                           ftxui::hbox({
                                               ftxui::paragraphAlignLeft("tak - wyświetli listę wszystkich przedmiotów"),
                                               ftxui::paragraphAlignRight("nie - przenosi do kolejnego ekranu odprawy")
                                           }) | color(ftxui::Color::GrayDark),

                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string response;
    std::cin >> response;

    if(response == "tak" || response == "Tak" || response == "TAK") {
        // TODO: wyświetlanie listy przedmiotów z bazy danych
        printAllItems(user);
    } else {
        return;
    }
}

