#include "Luggage.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "../functions/info_print_functions.h"

bool Luggage::confirmItems(User& user) {
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
        if (item.isForbidden() && item.getProfession() != user.profession) {
            errorFunction("Nie możesz zabrać tego przedmiotu ze sobą!", "Ten przedmiot jest zabroniony i dostępny tylko dla osób o zawodzie " + item.getProfession() + "!");
            return false;
        }
    }

    return checked;
}

void Luggage::getItemCount() {
    using namespace ftxui;

    std::vector<std::string> itemQuantities(items.size());
    std::vector<Component> itemInputs;

    for (size_t i = 0; i < items.size(); ++i) {
        size_t index = i;

        Component input_item_quantity = Input(&itemQuantities[index], items[index].getItemName());
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

    auto component = Container::Vertical(itemInputs);

    auto renderer = Renderer(component, [&] {
        Elements elements;
        for (size_t i = 0; i < items.size(); ++i) {
            elements.push_back(hbox(text(items[i].getItemName() + " : "), itemInputs[i]->Render()));
        }
        elements.push_back(text("Waga bagażu: " + std::to_string(totalWeight)));
        return vbox(elements) | border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
}