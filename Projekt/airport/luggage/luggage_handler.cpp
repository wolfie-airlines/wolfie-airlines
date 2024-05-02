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

  auto finishButton = Button("Potwierdź wybór", [&] {
    screen.ExitLoopClosure()();
  }) |
      ftxui::center | ftxui::bold | ftxui::borderEmpty;

  normal_checkbox_components.push_back(finishButton);

  auto specialCheckboxes = Container::Horizontal(CreateGroups(special_checkbox_components));
  auto normalCheckboxes = Container::Horizontal(CreateGroups(normal_checkbox_components));

  auto layout = Container::Vertical({
                                        specialCheckboxes,
                                        normalCheckboxes,
                                    });

  auto component = Renderer(layout, [&] {
    return vbox({
                    ftxui::hbox({ftxui::text(user.username_) | color(ftxui::Color::Gold1),
                                 ftxui::text(", wybierz rzeczy, które chcesz ze sobą wziąć:")}) |
                        ftxui::bold | ftxui::center,
                    ftxui::separator(),
                    ftxui::vbox({ftxui::paragraphAlignCenter(
                        "Wystarczy zaznaczyć elementy, które chcesz ze sobą zabrać, a my zajmiemy się resztą.")
                                     | ftxui::bold | color(ftxui::Color::YellowLight),
                                 ftxui::paragraphAlignCenter(
                                     "Pamiętaj, że jeśli wykonujesz konkretny zawód, przysługują ci korzyści odnośnie zabierania ze sobą rzeczy na pokład.")
                                     | ftxui::bold | color(ftxui::Color::Khaki3)}),
                    ftxui::separator(),
                    ftxui::vbox({
                                    ftxui::hbox({
                                                    ftxui::paragraphAlignCenter(
                                                        "Po zakończonym wybieraniu, kliknij w przycisk \"ZAKOŃCZ WYBIERANIE\".")
                                                        | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold,
                                                }),
                                    ftxui::separator(),
                                    ftxui::hbox({
                                                    ftxui::paragraphAlignCenter("SPECJAŁY")
                                                        | ftxui::color(ftxui::Color::Gold1) | ftxui::bold,
                                                }),
                                }),
                    ftxui::separator(),
                    hbox({
                             specialCheckboxes->Render() | ftxui::center,
                             separator(),
                             ftxui::vbox({
                                             ftxui::hbox({
                                                             ftxui::paragraphAlignCenter("ZWYKŁE")
                                                                 | ftxui::color(ftxui::Color::BlueLight) | ftxui::bold,
                                                         }),
                                             ftxui::separator(),
                                             normalCheckboxes->Render() | ftxui::center,
                                         }),
                         }),
                }) |
        xflex | border;
  });
  screen.Loop(component);

  std::vector<Item> selectedItems;
  for (size_t i = 0; i < items.size(); ++i) {
    if (*checkbox_states[i]) {
      selectedItems.push_back(items[i]);
    }
  }

  if (selectedItems.empty()) {
    PrintErrorMessage("Nie wybrano żadnych przedmiotów!", "Musisz wybrać co najmniej jeden przedmiot.");
    return;
  }

  double totalWeight = 0;
  for (const auto &item : selectedItems) {
    totalWeight += item.GetWeight();
  }

  Luggage luggage(selectedItems, totalWeight);

  auto result = luggage.ConfirmItems(user);
  bool confirmed = std::get<0>(result);
  std::string message = std::get<1>(result);

  if (confirmed) {
    double weight = luggage.ProcessItemsAndGetWeight();
    if (weight > luggage.max_allowed_weight_) {
      PrintErrorMessage("Bagaż przekracza dozwoloną wagę!", "Maksymalna waga bagażu to 32 kg.");
    } else if (weight > luggage.max_weight_) {
      double extraFee = luggage.CalculateOverweightFee(weight);
      const std::string titleMessage = "Nadpłata za przekroczenie wagi bagażu";
      bool paymentSuccess = AuthenticatePayment(user, user.payment_method_, titleMessage, extraFee);

      if (!paymentSuccess) {
        PrintErrorMessage("Nie udało się przetworzyć płatności.", "Odprawa bagażowa została przerwana.");
        return;
      }
      user.LuggageCheckin(flightNumber);
    } else {
      user.LuggageCheckin(flightNumber);
    }
  } else {
    PrintErrorMessage("Przerwano odprawę bagażu!", message);
  }
}

void PrintWelcomeInCheckIn(User &user) {
  mongocxx::cursor cursor = user.findUserInDatabase();
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie znaleziono użytkownika w bazie danych.", "Zaloguj się ponownie.");
    return;
  }

  bsoncxx::document::view userView = *cursor.begin();
  bsoncxx::document::element userFlightsElement = userView["user_flights_"];
  bsoncxx::array::view userFlightsArray = userFlightsElement.get_array().value;

  if (userFlightsArray.begin() == userFlightsArray.end()) {
    PrintErrorMessage("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
    return;
  }

  bool allCheckedIn = true;
  for (const auto &flight : userFlightsArray) {
    if (!flight["LuggageCheckin"].get_bool().value) {
      allCheckedIn = false;
      break;
    }
  }

  if (allCheckedIn) {
    PrintErrorMessage("Nie posiadasz żadnych biletów do odprawienia.", "");
    return;
  }

  std::optional<std::string> option = createTicketsScreen(user, true);
  if (option == "quit") {
    PrintErrorMessage("Anulowano odprawę.",
                      "Odprawa bagażowa została anulowana. Zawsze możesz wrócić do niej kiedy indziej.");
  } else if (option == "wybieram") {
    auto checkinScreen = [&] {
      auto summary = ftxui::vbox({
                                     ftxui::hbox({ftxui::paragraphAlignCenter("ODPRAWA BAGAŻOWA")}) |
                                         color(ftxui::Color::GrayDark),
                                     ftxui::separator(),
                                     ftxui::hbox({ftxui::paragraphAlignRight(
                                         "Podaj NUMER LOTU, na który chciałbyś odprawić swój bagaż:")}) |
                                         color(ftxui::Color::LightSteelBlue),
                                 });
      auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
      return std::make_shared<ftxui::Element>(document);
    };

    auto finalCheckinScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*checkinScreen()),
                                                    ftxui::Dimension::Fit(*checkinScreen()));
    ftxui::Render(finalCheckinScreen, *checkinScreen());
    std::cout << finalCheckinScreen.ToString() << '\0' << std::endl;

    int flightNumber;
    std::cin >> flightNumber;

    if (flightNumber < 1 || flightNumber > userFlightsArray.length()) {
      PrintErrorMessage("Nie ma takiego lotu.", "Spróbuj ponownie.");
      return;
    }

    if (userFlightsArray[flightNumber - 1]["LuggageCheckin"].get_bool().value) {
      PrintErrorMessage("Ten lot został już odprawiony.", "Wybierz inny lot.");
      return;
    }

    auto createScreen = [&] {
      auto summary = ftxui::vbox({
                                     ftxui::hbox({ftxui::text(user.username_) |
                                         color(ftxui::Color::Gold1),
                                                  ftxui::text(", witamy w odprawie bagażowej!")}) |
                                         ftxui::bold | ftxui::center,
                                     ftxui::separator(),
                                     ftxui::vbox({ftxui::paragraphAlignCenter(
                                         "Przed rozpoczęciem masz możliwość wyświetlenia listy wszystkich dozwolonych i zabronionych rzeczy do wzięcia do bagażu.")
                                                      |
                                                          ftxui::bold | color(ftxui::Color::YellowLight),
                                                  ftxui::paragraphAlignCenter("Chcesz to zrobić? ") |
                                                      ftxui::bold | color(ftxui::Color::Khaki3)}),
                                     ftxui::separator(),
                                     ftxui::vbox({
                                                     ftxui::hbox({
                                                                     ftxui::text(
                                                                         "tak. Wyświetla listę wszystkich przedmiotów")
                                                                         |
                                                                             ftxui::color(
                                                                                 ftxui::Color::CadetBlue) |
                                                                         ftxui::bold,
                                                                 }),
                                                     ftxui::hbox({
                                                                     ftxui::text(
                                                                         "nie. Przenosi do następnego ekranu odprawy") |
                                                                         ftxui::color(
                                                                             ftxui::Color::DarkOliveGreen2) |
                                                                         ftxui::bold,
                                                                 }),
                                                     ftxui::hbox({ftxui::text(
                                                         "quit. \U0001f51a Kończy odprawę") |
                                                         ftxui::color(
                                                             ftxui::Color::RedLight) |
                                                         ftxui::bold}),
                                                 }),
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

    if (response == "tak" || response == "Tak" || response == "TAK") {
      PrintAllItems(user);
    } else if (response == "nie" || response == "Nie" || response == "NIE") {
      CheckIn(user, flightNumber);
    } else {
      return;
    }
  }
}
