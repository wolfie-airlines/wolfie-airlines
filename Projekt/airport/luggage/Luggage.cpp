#include "Luggage.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "../functions/info_print_functions.h"

std::tuple<bool, std::string> Luggage::confirmItems(User& user) {
    ftxui::Elements elements;
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    for (const auto& item : items) {
        elements.push_back(
                ftxui::hbox(
                        ftxui::text("• " + item.getItemName()) | ftxui::bold
                ) | color(ftxui::Color::LightSteelBlue1)
              );
    }

    std::vector<ftxui::Component> vertical_containers;
    bool checked = false;
    auto yesButton = ftxui::Button("Tak", [&] {
        screen.ExitLoopClosure()();
        checked = true;
    }) | ftxui::center | ftxui::bold | ftxui::borderEmpty;

    auto noButton = ftxui::Button("Nie", [&] {
        screen.ExitLoopClosure()();
    }) | ftxui::center | ftxui::bold | ftxui::borderEmpty;

    vertical_containers.push_back(yesButton);
    vertical_containers.push_back(noButton);

    auto buttons = ftxui::Container::Horizontal(vertical_containers);

    auto layout = ftxui::Container::Horizontal({buttons});

    auto component = Renderer(layout, [&] {
        return ftxui::vbox({
                                   ftxui::hbox({
                                                       ftxui::paragraphAlignCenter("POTWIERDŹ ZAWARTOŚĆ BAGAŻU") | ftxui::bold
                                               }) | color(ftxui::Color::MediumOrchid1),
                                   ftxui::separator(),
                                   ftxui::vbox({elements}),
                                   ftxui::separator(),
                                   ftxui::hbox({
                                                       ftxui::paragraphAlignCenter("Czy wszystkie przedmioty się zgadzają?") | ftxui::bold | color(ftxui::Color::YellowLight)
                                               }),
                                      ftxui::separator(),
                                   buttons->Render() | ftxui::center,
                           }) | ftxui::border  | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    });

    screen.Loop(component);

    for (const auto& item : items) {
        if (item.isForbidden() && item.getProfession() != user.profession && !item.getProfession().empty()) {
            std::string message = "Przedmiot " + item.getItemName() + " jest zabroniony/dostępny tylko dla osób o zawodzie " + item.getProfession() + "!";
            return {false, message};
        } else if (item.isForbidden() && item.getProfession().empty()) {
            std::string message = "Przedmiot " + item.getItemName() + " jest zabroniony!";
            return {false, message};
        }
    }

    if(!checked) {
        return {false, "Nie potwierdzono zawartości bagażu!"};
    } else {
        return {true, ""};
    }
}

void Luggage::getItemCount() {
    using namespace ftxui;

    std::vector<std::string> itemQuantities(items.size());
    std::vector<Component> itemInputs;
    auto screen = ScreenInteractive::TerminalOutput();

    for (size_t i = 0; i < items.size(); ++i) {
        size_t index = i;

        Component input_item_quantity = Input(&itemQuantities[index], "Podaj ilość dla " + items[index].getItemName());
        input_item_quantity |= CatchEvent([&, index](const Event& event) {
            if (event.is_character() && (!std::isdigit(event.character()[0]) || itemQuantities[index].size() > 3)) {
                return true;
            }
            totalWeight = 0;
            for (size_t j = 0; j < items.size(); ++j) {
                totalWeight += itemQuantities[j].empty() ? 0 : std::stoi(itemQuantities[j]) * items[j].getWeight();
            }
            return false;
        });
        itemInputs.push_back(input_item_quantity);
    }

    auto finalButton = Button("Potwierdź", [&] {
        screen.ExitLoopClosure()();
    }) | color(Color::YellowLight) | size(WIDTH, LESS_THAN, 20);

    itemInputs.push_back(finalButton);

    auto layout = ftxui::Container::Vertical({
                                                     itemInputs,
                                             });


    auto component = Container::Vertical(itemInputs);

    auto renderer = Renderer(component, [&] {
        Elements elements;
        for (size_t i = 0; i < items.size(); ++i) {
            elements.push_back(hbox(text(items[i].getItemName() + " : "), itemInputs[i]->Render()));
        }
        elements.push_back(finalButton->Render());
        elements.push_back(text("Waga bagażu: " + std::to_string(totalWeight)));
        return vbox({
                                hbox({
                                            paragraph("Podaj ilość przedmiotów, które chcesz zabrać ze sobą:") | bold
                                    }) | color(Color::MediumOrchid1),
                                separator(),
                                vbox(elements),
        }) | border | size(ftxui::WIDTH, ftxui::LESS_THAN, 120);
    });

    screen.Loop(renderer);



    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << items[i].getItemName() << " : " << itemQuantities[i] << std::endl;
        //TODO: obliczanie wagi bagażu czy przekracza czy nie przekracza limitu
        // jeśli przekracza limit 20kg, obliczana jest nadpłata za każdy kilogram aż do 32kg
        // jeśli przekracza 32kg, bagaż nie zostanie przyjęty
        // po zapłaceniu nadpłaty, bagaż zostanie przyjęty -> do bazy danych
    }
}