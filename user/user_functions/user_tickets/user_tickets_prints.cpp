#include "user_tickets_prints.h"

#include "../../../functions/info_prints/info_prints.h"
#include "ftxui/dom/elements.hpp"

std::optional<std::string> CreateTicketsScreen(User &user, bool is_checkin) {
  mongocxx::cursor cursor = user.FindUserInDatabase();
  if (cursor.begin() == cursor.end()) {
    PrintErrorMessage("Nie znaleziono użytkownika w bazie danych.", "Zaloguj się ponownie.");
    return {};
  }

  bsoncxx::document::view user_view = *cursor.begin();
  bsoncxx::document::element user_flights_element = user_view["userFlights"];
  bsoncxx::array::view user_flights = user_flights_element.get_array().value;

  std::vector<FlightInfo> flights_info;
  for (const auto &flight : user_flights) {
    FlightInfo info;
    info.flight_id = flight["flightId"].get_string().value;
    info.departure = flight["departure"].get_string().value;
    info.destination = flight["destination"].get_string().value;
    info.departure_time = flight["departureTime"].get_string().value;
    info.price = flight["price"].get_double().value;
    for (const auto &seat : flight["seats"].get_array().value) {
      info.seats.push_back(seat.get_int32().value);
    }
    info.checkin = flight["checkin"].get_bool().value;
    info.luggage_checkin = flight["luggageCheckin"].get_bool().value;
    flights_info.push_back(info);
  }

  int current_page = 1;
  int total_tickets = 0;
  for (const auto &flightInfo : flights_info) {
    total_tickets += flightInfo.seats.size();
  }

  int total_pages = (total_tickets + PAGE_SIZE - 1) / PAGE_SIZE;

  while (true) {
    int start_index = (current_page - 1) * PAGE_SIZE;
    int end_index = start_index + PAGE_SIZE;

    ftxui::Elements elements;
    int current_ticket = 0;
    int flight_number = 1;
    for (auto &flight_info : flights_info) {
      flight_info.flight_number = flight_number;
      flight_number++;
      for (const auto &seat : flight_info.seats) {
        if (current_ticket >= start_index && current_ticket < end_index) {
          std::string row = std::to_string(seat % 9 == 0 ? seat / 9 : seat / 9 + 1);
          std::string seat_str = std::to_string(seat % 9 == 0 ? 9 : seat % 9);
          std::string place_in_plane = "Rząd: ";
          place_in_plane += row;
          place_in_plane += ", Miejsce: ";
          place_in_plane += seat_str;
          std::string checkin = flight_info.checkin ? "✅" : "❌";
          std::string luggage_checkin = flight_info.luggage_checkin ? "✅" : "❌";
          auto ticket_content = ftxui::hbox({
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("ID LOTU: ") |
                                                                    ftxui::bold | color(ftxui::Color::DarkSeaGreen4),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(flight_info.flight_id) |
                                                                    ftxui::bold | color(ftxui::Color::DarkSeaGreen4),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("MIEJSCE ODLOTU: ") |
                                                                    ftxui::bold | color(ftxui::Color::SteelBlue),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(flight_info.departure) |
                                                                    ftxui::bold | color(ftxui::Color::SteelBlue),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("MIEJSCE PRZYLOTU: ") |
                                                                    ftxui::bold | color(ftxui::Color::SteelBlue3),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(
                                                                    flight_info.destination) |
                                                                    ftxui::bold |
                                                                    color(ftxui::Color::SteelBlue3),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("CZAS WYLOTU: ") |
                                                                    ftxui::bold | color(ftxui::Color::Aquamarine3),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(
                                                                    flight_info.departure_time) |
                                                                    ftxui::bold |
                                                                    color(ftxui::Color::Aquamarine3),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("MIEJSCE W SAMOLOCIE") |
                                                                    ftxui::bold | color(ftxui::Color::LightPink4),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(place_in_plane) |
                                                                    ftxui::bold | color(ftxui::Color::LightPink4),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("ODPRAWIONY: ") |
                                                                    ftxui::bold | color(ftxui::Color::PaleGreen3),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(checkin) |
                                                                    ftxui::bold | color(ftxui::Color::PaleGreen3),
                                                            }),
                                                ftxui::separator(),
                                                ftxui::vbox({
                                                                ftxui::paragraphAlignCenter("ODPRAWA BAGAŻOWA: ") |
                                                                    ftxui::bold | color(ftxui::Color::PaleGreen3),
                                                                ftxui::separator(),
                                                                ftxui::paragraphAlignCenter(luggage_checkin) |
                                                                    ftxui::bold | color(ftxui::Color::PaleGreen3),
                                                            }),
                                            }) |
              ftxui::border;
          elements.push_back(window(ftxui::paragraphAlignCenter("LOT #" + std::to_string(flight_info.flight_number)),
                                    ticket_content));
        }
        current_ticket++;
      }
    }

    auto screen = [&] {
      auto summary = ftxui::vbox({
                                     ftxui::hbox({ftxui::paragraphAlignCenter("TWOJE BILETY")}) |
                                         color(ftxui::Color::White),
                                     ftxui::separator(),
                                     ftxui::vbox(elements),
                                 });
      auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
      if (total_pages > 1) {
        auto navigation = ftxui::vbox({ftxui::hbox({ftxui::paragraphAlignCenter("NAWIGACJA 🧭")}) |
            color(ftxui::Color::White),
                                       ftxui::separator(),
                                       ftxui::hbox({
                                                       ftxui::paragraphAlignLeft(
                                                           "Strona: " + std::to_string(current_page) + "/"
                                                               + std::to_string(total_pages)) |
                                                           color(ftxui::Color::White),
                                                   }),
                                       ftxui::separator(),
                                       ftxui::hbox({
                                                       ftxui::vbox({
                                                                       ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'prev' aby wrócić do poprzedniej strony.")
                                                                           |
                                                                               color(ftxui::Color::SteelBlue),
                                                                       ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'next' aby przejść do następnej strony.")
                                                                           |
                                                                               color(ftxui::Color::YellowLight),
                                                                       is_checkin ? ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'quit' aby zakończyć odprawę.") |
                                                                           color(ftxui::Color::RedLight)
                                                                                  : ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'quit' aby wyjść z przeglądania biletów.")
                                                                           |
                                                                               color(ftxui::Color::RedLight),
                                                                       is_checkin ? ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'wybieram' aby przejść do wyboru biletu do odprawienia.")
                                                                           |
                                                                               color(ftxui::Color::GreenLight)
                                                                                  : ftxui::paragraphAlignLeft(
                                                                           "Dziękujemy za wybór Wolfie Airlines") |
                                                                           color(ftxui::Color::GreenLight),
                                                                   }),
                                                   })}) |
            ftxui::border;
        document = ftxui::vbox({document, navigation});
      } else if (is_checkin) {
        auto navigation = ftxui::vbox({ftxui::hbox({ftxui::paragraphAlignCenter("ODPRAWA 🎫")}) |
            color(ftxui::Color::White),
                                       ftxui::separator(),
                                       ftxui::hbox({
                                                       ftxui::vbox({
                                                                       ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'quit' aby zakończyć odprawę.") |
                                                                           color(ftxui::Color::RedLight),
                                                                       ftxui::paragraphAlignLeft(
                                                                           "Wpisz 'wybieram' aby przejść do wyboru biletu do odprawienia")
                                                                           |
                                                                               color(ftxui::Color::GreenLight),
                                                                   }),
                                                   })}) |
            ftxui::border;
        document = ftxui::vbox({document, navigation});
      }
      return std::make_shared<ftxui::Element>(document);
    };

    auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(*screen()),
                                             ftxui::Dimension::Fit(*screen()));
    ftxui::Render(user_screen, *screen());
    std::cout << user_screen.ToString() << '\0' << std::endl;

    if (total_pages > 1) {
      std::string input;
      std::cin >> input;

      if (input == "next" && current_page < total_pages) {
        current_page++;
      } else if (input == "prev" && current_page > 1) {
        current_page--;
      } else if (input == "quit") {
        if (is_checkin) {
          return "quit";
        } else {
          break;
        }
      } else if (input == "wybieram" && is_checkin) {
        return "wybieram";
      }
    } else if (is_checkin) {
      std::string input;
      std::cin >> input;
      if (input == "quit") {
        return "quit";
      } else if (input == "wybieram") {
        return "wybieram";
      }
    } else {
      break;
    }
  }
  return {};
}