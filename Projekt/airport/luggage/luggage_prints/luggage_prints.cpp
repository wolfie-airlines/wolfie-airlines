#include "luggage_prints.h"
#include "ftxui/dom/elements.hpp"
#include "../item/Item.h"

void printAllItems(User& user) {
    auto collection = user.getSpecificCollection("luggage_list");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto &&doc: cursor) {
        documents.push_back(doc);
    }

    std::vector<Item> items;
    for (const auto& item : documents) {
        std::string itemName = (std::string) item["item"].get_string().value;
        std::cout << itemName << std::endl;

        std::string description;
        if(item["description"]) {
            description = (std::string) item["description"].get_string().value;
        }

        std::vector<std::string> hints;
        if(item["hints"]) {
            for (const auto& hint : item["hints"].get_array().value) {
                hints.push_back((std::string) hint.get_string().value);
            }
        }

        bool forbidden = item["forbidden"].get_bool().value;
        bool registeredLuggage = item["registeredLuggage"].get_bool().value;
        bool handLuggage = item["handLuggage"].get_bool().value;
        bool pilotAllowance = item["pilotAllowance"].get_bool().value;
        double maxCount;
        if (item["maxCount"].type() == bsoncxx::type::k_double) {
            maxCount = item["maxCount"].get_double().value;
        } else {
            maxCount = static_cast<double>(item["maxCount"].get_int32().value);
        }

        double weight;
        if (item["weightForOne"].type() == bsoncxx::type::k_double) {
            weight = item["weightForOne"].get_double().value;
        } else {
            weight = static_cast<double>(item["weightForOne"].get_int32().value);
        }
        items.emplace_back(
                Item(itemName, description, hints, forbidden, registeredLuggage, handLuggage, pilotAllowance, maxCount, weight)
                );
    }

        ftxui::Elements elements;
    std::cout << items.size() << std::endl;
        for(const auto& item : items) {
            auto itemElement = ftxui::vbox({
                ftxui::hbox({ftxui::text("Przedmiot: " + item.getItemName()) | ftxui::bold}),
                ftxui::hbox({ftxui::text("Opis: " + item.getDescription())}),
//                ftxui::hbox({ftxui::text("Wskazówki: ") | ftxui::bold}),
//                ftxui::hbox({ftxui::text("Zabroniony: " + std::to_string(item.isForbidden()))}),
//                ftxui::hbox({ftxui::text("Bagaż rejestrowany: " + std::to_string(item.isRegisteredLuggage()))}),
//                ftxui::hbox({ftxui::text("Bagaż podręczny: " + std::to_string(item.isHandLuggage()))}),
//                ftxui::hbox({ftxui::text("Dla pilotów: " + std::to_string(item.isPilotAllowance()))}),
//                ftxui::hbox({ftxui::text("Maksymalna ilość: " + std::to_string(item.getMaxCount()))}),
//                ftxui::hbox({ftxui::text("Waga: " + std::to_string(item.getWeight()))}),
                ftxui::separator()
            });
            elements.push_back(itemElement);
        }

        std::cout << elements.size() << std::endl;

        auto document = ftxui::vbox(elements);


        auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
        ftxui::Render(screen, document);
        std::cout << screen.ToString() << '\0' << std::endl;
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

