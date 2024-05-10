#include "luggage_handler.h"

#include "../functions/info_prints/info_prints.h"
#include "../user/user_functions/user_payments/user_payment_functions.h"
#include "../user/user_functions/user_tickets/user_tickets_prints.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "item/item_handler.h"
#include "luggage_prints/luggage_prints.h"

void CheckIn(User &user, int flightNumber) {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<Item> items = GetItems(user);

    std::vector<Component> special_checkbox_components;
    std::vector<Component> normal_checkbox_components;
    std::vector<std::shared_ptr<bool>> checkbox_states(items.size());

    for (size_t i = 0; i < items.size(); ++i) {
        checkbox_states[i] = std::make_shared<bool>(false);
        CheckboxOption option;
        option.label = items[i].GetItemName();
        option.checked = checkbox_states[i].get();
        ftxui::Color itemColor =
            items[i].IsForbidden() && items[i].GetProfession() != user.profession_ ? ftxui::Color::RedLight
                                                                                   : ftxui::Color::White;
        auto checkbox = Checkbox(option) | ftxui::color(itemColor);
        if (items[i].GetCategory() == "normal") {
            normal_checkbox_components.push_back(checkbox);
        } else {
            special_checkbox_components.push_back(checkbox);
        }
    }

    auto finish_button = Button("Confirm selection", [&] {
                             screen.ExitLoopClosure()();
                         }) |
                         ftxui::center | ftxui::bold | ftxui::borderEmpty;

    normal_checkbox_components.push_back(finish_button);

    auto special_checkboxes = Container::Horizontal(CreateGroups(special_checkbox_components));
    auto normal_checkboxes = Container::Horizontal(CreateGroups(normal_checkbox_components));

    auto layout = Container::Vertical({
        special_checkboxes,
        normal_checkboxes,
    });

    auto component = Renderer(layout, [&] {
        return vbox({
                   ftxui::hbox({ftxui::text(user.username_) | color(ftxui::Color::Gold1),
                                ftxui::text(", Choose the things you want to take with you:")}) |
                       ftxui::bold | ftxui::center,
                   ftxui::separator(),
                   ftxui::vbox({ftxui::paragraphAlignCenter(
                                    "Just select the items you want to bring with you and we'll take care of the rest.") |
                                    ftxui::bold | color(ftxui::Color::YellowLight),
                                ftxui::paragraphAlignCenter(
                                    "Remember that if you have a specific profession, you are entitled to benefits with regard to taking things on board with you.") |
                                    ftxui::bold | color(ftxui::Color::Khaki3)}),
                   ftxui::separator(),
                   ftxui::vbox({
                       ftxui::hbox({
                           ftxui::paragraphAlignCenter(
                               "When the selection is complete, click on the \"FINISH\".") |
                               ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                       }),
                       ftxui::separator(),
                       ftxui::hbox({
                           ftxui::paragraphAlignCenter("SPECIAL") | ftxui::color(ftxui::Color::Gold1) | ftxui::bold,
                       }),
                   }),
                   ftxui::separator(),
                   hbox({
                       special_checkboxes->Render() | ftxui::center,
                       separator(),
                       ftxui::vbox({
                           ftxui::hbox({
                               ftxui::paragraphAlignCenter("COMMON") | ftxui::color(ftxui::Color::BlueLight) | ftxui::bold,
                           }),
                           ftxui::separator(),
                           normal_checkboxes->Render() | ftxui::center,
                       }),
                   }),
               }) |
               xflex | border;
    });
    screen.Loop(component);

    std::vector<Item> selected_items;
    for (size_t i = 0; i < items.size(); ++i) {
        if (*checkbox_states[i]) {
            selected_items.push_back(items[i]);
        }
    }

    if (selected_items.empty()) {
        PrintErrorMessage("No items have been selected!", "You must choose at least one item.");
        return;
    }

    double total_weight = 0;
    for (const auto &item : selected_items) {
        total_weight += item.GetWeight();
    }

    Luggage luggage(selected_items, total_weight);

    auto result = luggage.ConfirmItems(user);
    bool confirmed = std::get<0>(result);
    std::string message = std::get<1>(result);

    if (confirmed) {
        double weight = luggage.ProcessItemsAndGetWeight();
        if (weight > luggage.max_allowed_weight_) {
            PrintErrorMessage("Luggage exceeds the allowed weight!", "The maximum weight of luggage is 32 kg.");
        } else if (weight > luggage.max_weight_) {
            double extra_fee = luggage.CalculateOverweightFee(weight);
            const std::string kTitleMessage = "Payment for excessing the baggage weight";
            bool authenticate_payment = AuthenticatePayment(user, user.payment_method_, kTitleMessage, extra_fee);

            if (!authenticate_payment) {
                PrintErrorMessage("The payment could not be processed.", "The baggage check was interrupted");
                return;
            }
            user.LuggageCheckin(flightNumber);
        } else {
            user.LuggageCheckin(flightNumber);
        }
    } else {
        PrintErrorMessage("Baggage checkin has been interrupted!", message);
    }
}