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

  auto finish_button = Button("Potwierdź wybór", [&] {
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
                             special_checkboxes->Render() | ftxui::center,
                             separator(),
                             ftxui::vbox({
                                             ftxui::hbox({
                                                             ftxui::paragraphAlignCenter("ZWYKŁE")
                                                                 | ftxui::color(ftxui::Color::BlueLight) | ftxui::bold,
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
    PrintErrorMessage("Nie wybrano żadnych przedmiotów!", "Musisz wybrać co najmniej jeden przedmiot.");
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
      PrintErrorMessage("Bagaż przekracza dozwoloną wagę!", "Maksymalna waga bagażu to 32 kg.");
    } else if (weight > luggage.max_weight_) {
      double extra_fee = luggage.CalculateOverweightFee(weight);
      const std::string kTitleMessage = "Nadpłata za przekroczenie wagi bagażu";
      bool authenticate_payment = AuthenticatePayment(user, user.payment_method_, kTitleMessage, extra_fee);

      if (!authenticate_payment) {
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
  mongocxx::cursor cursor = user.FindUserInDatabase();
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie znaleziono użytkownika w bazie danych.", "Zaloguj się ponownie.");
    return;
  }

  bsoncxx::document::view user_view = *cursor.begin();
  bsoncxx::document::element user_flights_element = user_view["userFlights"];
  bsoncxx::array::view user_flights = user_flights_element.get_array().value;

  if (user_flights.begin() == user_flights.end()) {
    PrintErrorMessage("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
    return;
  }

  bool all_checked_in = true;
  for (const auto &flight : user_flights) {
    if (!flight["luggageCheckin"].get_bool().value) {
      all_checked_in = false;
      break;
    }
  }

  if (all_checked_in) {
    PrintErrorMessage("Nie posiadasz żadnych biletów do odprawienia.", "");
    return;
  }

  std::optional<std::string> option = CreateTicketsScreen(user, true);
  if (option == "quit") {
    PrintErrorMessage("Anulowano odprawę.",
                      "Odprawa bagażowa została anulowana. Zawsze możesz wrócić do niej kiedy indziej.");
  } else if (option == "wybieram") {
    auto checkin_screen = [&] {
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

    auto final_checkin_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(*checkin_screen()),
                                                      ftxui::Dimension::Fit(*checkin_screen()));
    ftxui::Render(final_checkin_screen, *checkin_screen());
    std::cout << final_checkin_screen.ToString() << '\0' << std::endl;

    int flight_number;
    std::cin >> flight_number;

    if (flight_number < 1 || flight_number > user_flights.length()) {
      PrintErrorMessage("Nie ma takiego lotu.", "Spróbuj ponownie.");
      return;
    }

    if (user_flights[flight_number - 1]["luggageCheckin"].get_bool().value) {
      PrintErrorMessage("Ten lot został już odprawiony.", "Wybierz inny lot.");
      return;
    }

    auto create_screen = [&] {
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

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
    ftxui::Render(user_screen, *create_screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    std::string response;
    std::cin >> response;

    if (response == "tak" || response == "Tak" || response == "TAK") {
      PrintAllItems(user);
    } else if (response == "nie" || response == "Nie" || response == "NIE") {
      CheckIn(user, flight_number);
    } else {
      return;
    }
  }
}
