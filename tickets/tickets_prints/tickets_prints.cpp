#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <shellapi.h>

#include "tickets_prints.h"
#include <iomanip>

#include "../../functions/info_prints/info_prints.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "qrcodegen.hpp"

int CreateTicketMenu() {
  using namespace ftxui;
  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> entries = {
      "Kup bilet (podając Indentyfikator <ID> lotu)",
      "Kup bilet (podając miasto wylotu i przylotu)",
      "\U0001F519 Wróć do menu głównego",
  };
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu = Menu(&entries, &selected, option);

  screen.Loop(menu);
  return selected;
}

bool ValidChoice(const std::string &choice_title, const std::string &choice_text) {
  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(choice_title)})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(choice_text) | ftxui::bold | color(ftxui::Color::Green)}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::cin >> answer;

  if (answer == "tak" || answer == "Tak" || answer == "TAK")
    return true;
  else
    return false;
}

void PrintTicketInvoice(
    User &user, FlightConnection &found_connection, const std::vector<int> &selected_seats) {
  time_t now = time(nullptr);
  tm ltm{};
  localtime_s(&ltm, &now);
  std::string date =
      std::to_string(1900 + ltm.tm_year) + "-" + std::to_string(1 + ltm.tm_mon) + "-" + std::to_string(ltm.tm_mday);

  std::ostringstream stream_price;
  stream_price << std::fixed << std::setprecision(2) << found_connection.GetPrice() * selected_seats.size();
  std::string total_price = stream_price.str();

  std::ostringstream stream_discount;
  stream_discount << std::fixed << std::setprecision(2) << (found_connection.GetPrice() * selected_seats.size()
      - found_connection.GetPrice() * selected_seats.size() * user.discount_);
  std::string how_much_discount = stream_discount.str();

  std::ostringstream stream_target_price;
  stream_target_price << std::fixed << std::setprecision(2)
                    << found_connection.GetPrice() * selected_seats.size() * user.discount_;
  std::string target_price = stream_target_price.str();

  ftxui::Elements elements;
  elements.reserve(selected_seats.size());
  for (const auto &ticket : selected_seats) {
    std::string place_in_plane =
        "Rząd: " + std::to_string((ticket % 9 == 0 ? ticket / 9 : ticket / 9 + 1)) + ", Miejsce: "
            + std::to_string((ticket % 9 == 0 ? 9 : ticket % 9));
    elements.push_back(ftxui::hbox({
                                       ftxui::paragraphAlignLeft("ID LOTU: " + found_connection.GetIdentifier())
                                           | ftxui::bold | color(ftxui::Color::GrayLight),
                                       ftxui::paragraphAlignLeft(
                                           "MIEJSCE ODLOTU: " + found_connection.GetDepartureCity()) | ftxui::bold
                                           | color(ftxui::Color::GrayLight),
                                       ftxui::paragraphAlignLeft(
                                           "MIEJSCE PRZYLOTU: " + found_connection.GetDestinationCity()) | ftxui::bold
                                           | color(ftxui::Color::GrayLight),
                                       ftxui::paragraphAlignLeft("CZAS WYLOTU: " + found_connection.GetDepartureTime())
                                           | ftxui::bold | color(ftxui::Color::GrayLight),
                                       ftxui::paragraphAlignLeft(place_in_plane) | ftxui::bold
                                           | color(ftxui::Color::GrayLight),
                                   }) |
        ftxui::border);
  }

  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter("POTWIERDZENIE ZAKUPU BILETÓW")})
                                       | color(ftxui::Color::White),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::paragraphAlignLeft("Data: " + date) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft("E-mail: " + user.email_) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft("Użytkownik: " + user.username_) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight)}),
                                   ftxui::separator(),
                                   ftxui::vbox(elements),
                                   ftxui::separator(),
                                   ftxui::hbox({
                                                   ftxui::paragraphAlignRight("Cena: " + total_price + " PLN")
                                                       | ftxui::bold | color(ftxui::Color::Gold3),
                                               }),
                                   ftxui::hbox({
                                                   ftxui::paragraphAlignRight("Zniżka: " + how_much_discount + " PLN")
                                                       | ftxui::bold | color(ftxui::Color::SteelBlue1),
                                               }),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::paragraphAlignRight("Zapłacono: " + target_price + " PLN")
                                                    | ftxui::bold | color(ftxui::Color::Gold1)}),
                                   ftxui::hbox({ftxui::text(
                                       L"ODPRAW SIĘ ONLINE JUŻ TERAZ! Przejdź do zakładki 'Moje bilety'!")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;
}

void OpenWebsite() {
  std::string search_url = "https://wolfie-airlines-webpage.vercel.app/odprawy";
  PrintErrorMessage("Pamiętaj!", "Żeby dokonać odprawy musisz mieć zakupiony bilet.");
  ShellExecuteA(NULL, "open", search_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}