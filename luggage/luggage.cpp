#include "luggage.h"

#include "../functions/info_prints/info_prints.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

std::tuple<bool, std::string> Luggage::ConfirmItems(User &user) {
    ftxui::Elements elements;
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    for (const auto &item : items_) {
        elements.push_back(
            ftxui::hbox(
                ftxui::text("• " + item.GetItemName()) | ftxui::bold) |
            color(ftxui::Color::LightSteelBlue1));
    }

    std::vector<ftxui::Component> vertical_containers;
    bool checked = false;
    auto yes_button = ftxui::Button("Yes", [&] {
                          screen.ExitLoopClosure()();
                          checked = true;
                      }) |
                      ftxui::center | ftxui::bold | ftxui::borderEmpty;

    auto no_button = ftxui::Button("No", [&] {
                         screen.ExitLoopClosure()();
                     }) |
                     ftxui::center | ftxui::bold | ftxui::borderEmpty;

    vertical_containers.push_back(yes_button);
    vertical_containers.push_back(no_button);

    auto buttons = ftxui::Container::Horizontal(vertical_containers);

    auto layout = ftxui::Container::Horizontal({buttons});

    auto component = Renderer(layout, [&] {
        return ftxui::vbox({
                   ftxui::hbox({ftxui::paragraphAlignCenter("CONFIRM BAGGAGE CONTENTS") | ftxui::bold}) | color(ftxui::Color::MediumOrchid1),
                   ftxui::separator(),
                   ftxui::vbox({elements}),
                   ftxui::separator(),
                   ftxui::hbox({ftxui::paragraphAlignCenter("Do all the items match up?") | ftxui::bold | color(ftxui::Color::YellowLight)}),
                   ftxui::separator(),
                   buttons->Render() | ftxui::center,
               }) |
               ftxui::border | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    });

    screen.Loop(component);

    for (const auto &item : items_) {
        if (item.IsForbidden() && item.GetProfession() != user.profession_ && !item.GetProfession().empty()) {
            std::string message = "Item " + item.GetItemName() + " is forbidden/accessible only to people with a profession " + item.GetProfession() + "!";
            return {false, message};
        } else if (item.IsForbidden() && item.GetProfession().empty()) {
            std::string message = "Item " + item.GetItemName() + " is forbidden!";
            return {false, message};
        }
    }

    if (!checked) {
        return {false, "The contents of the luggage have not been confirmed!"};
    } else {
        return {true, ""};
    }
}

double Luggage::ProcessItemsAndGetWeight() {
    using namespace ftxui;

    std::vector<std::string> item_quantities(items_.size());
    std::vector<Component> item_inputs;
    auto screen = ScreenInteractive::TerminalOutput();

    for (size_t i = 0; i < items_.size(); ++i) {
        size_t index = i;

        Component input_item_quantity = Input(&item_quantities[index], "Enter the quantity for " + items_[index].GetItemName());
        input_item_quantity |= CatchEvent([&, index](const Event &event) {
            if (event.is_character() && (!std::isdigit(event.character()[0]) || item_quantities[index].size() > 3)) {
                return true;
            }
            total_weight_ = 0;
            for (size_t j = 0; j < items_.size(); ++j) {
                total_weight_ += item_quantities[j].empty() ? 0 : std::stoi(item_quantities[j]) * items_[j].GetWeight();
            }
            return false;
        });
        item_inputs.push_back(input_item_quantity);
    }

    auto final_button = Button("FINISH", [&] {
                            screen.ExitLoopClosure()();
                        }) |
                        color(Color::YellowLight) | size(WIDTH, LESS_THAN, 20);

    item_inputs.push_back(final_button);

    auto layout = ftxui::Container::Vertical({
        item_inputs,
    });

    auto component = Container::Vertical(item_inputs);

    auto renderer = Renderer(component, [&] {
        Elements elements;
        for (size_t i = 0; i < items_.size(); ++i) {
            elements.push_back(hbox(text(items_[i].GetItemName() + " : "), item_inputs[i]->Render()));
        }
        elements.push_back(final_button->Render());
        elements.push_back(text("Luggage weight: " + std::to_string(total_weight_)));
        return vbox({
                   hbox({paragraph("Specify the number of items you want to take with you:") | bold}) | color(Color::MediumOrchid1),
                   separator(),
                   hbox({paragraph("In Wolfie Airlines, any baggage up to 20kg is completely free!") | bold}) | color(Color::GreenLight),
                   separator(),
                   vbox(elements),
               }) |
               border | size(ftxui::WIDTH, ftxui::LESS_THAN, 100);
    });

    screen.Loop(renderer);

    double weight = 0;
    for (size_t i = 0; i < items_.size(); ++i) {
        if (item_quantities[i].empty() || item_quantities[i] == "0") {
            PrintErrorMessage("The quantity of the " + items_[i].GetItemName() + " is not given!", "Try again.");
            return -1;
        }

        weight += std::stoi(item_quantities[i]) * items_[i].GetWeight();
    }

    return weight;
}

double Luggage::CalculateOverweightFee(double weight) const {
    double extra_weight = weight - 20;
    double extra_fee = extra_weight * overweight_fee_per_kg_ * euro_to_pln_;
    return extra_fee;
}
