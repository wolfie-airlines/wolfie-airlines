#include "user_tickets_print_functions.h"
#include "../../functions/info_print_functions.h"
#include "ftxui/dom/elements.hpp"

void createTicketsScreen(User& user) {
    bsoncxx::document::value filter_builder = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("email", user.email),
            bsoncxx::builder::basic::kvp("password", user.getPassword())
    );

    bsoncxx::document::view filter_view = filter_builder.view();
    mongocxx::cursor cursor = user.getCollection().find(filter_view);
    if (cursor.begin() == cursor.end()) {
        errorFunction("Nie udało się znaleźć użytkownika w bazie danych.", "");
        return;
    }

    bsoncxx::document::view userView = *cursor.begin();
    bsoncxx::document::element userFlightsElement = userView["userFlights"];
    bsoncxx::array::view userFlightsArray = userFlightsElement.get_array().value;

    if (userFlightsArray.begin() == userFlightsArray.end()) {
        errorFunction("Nie posiadasz żadnych biletów.", "Zakup je już teraz korzystając z opcji 2!");
        return;
    }

    std::vector<FlightInfo> flightsInfo;
    for (const auto &flight: userFlightsArray) {
        FlightInfo info;
        info.flightId = flight["flightId"].get_string().value;
        info.departure = flight["departure"].get_string().value;
        info.destination = flight["destination"].get_string().value;
        info.departureTime = flight["departureTime"].get_string().value;
        info.price = flight["price"].get_double().value;
        for (const auto &seat: flight["seats"].get_array().value) {
            info.seats.push_back(seat.get_int32().value);
        }
        info.checkin = flight["checkin"].get_bool().value;
        flightsInfo.push_back(info);
    }

    ftxui::Elements elements;
    int flightNumber = 1;
    for (auto &flightInfo: flightsInfo) {
        flightInfo.flightNumber = flightNumber;
        flightNumber++;
        for (const auto &seat: flightInfo.seats) {
            std::string row = std::to_string(seat % 9 == 0 ? seat / 9 : seat / 9 + 1);
            std::string seatStr = std::to_string(seat % 9 == 0 ? 9 : seat % 9);
            std::string placeInPlane = "Rząd: ";
            placeInPlane += row;
            placeInPlane += ", Miejsce: ";
            placeInPlane += seatStr;
            std::string checkin = flightInfo.checkin ? "✅" : "❌";
            auto ticketContent = ftxui::hbox({
                                                   ftxui::vbox({
                                                                       ftxui::paragraphAlignCenter("ID LOTU: ") |
                                                                       ftxui::bold | color(ftxui::Color::DarkSeaGreen4),
                                                                       ftxui::separator(),
                                                                       ftxui::paragraphAlignCenter(flightInfo.flightId) |
                                                                       ftxui::bold | color(ftxui::Color::DarkSeaGreen4),
                                                               }),
                                                   ftxui::separator(),
                                                   ftxui::vbox({
                                                                       ftxui::paragraphAlignCenter("MIEJSCE ODLOTU: ") |
                                                                       ftxui::bold | color(ftxui::Color::SteelBlue),
                                                                       ftxui::separator(),
                                                                       ftxui::paragraphAlignCenter(flightInfo.departure) |
                                                                       ftxui::bold | color(ftxui::Color::SteelBlue),
                                                               }),
                                                   ftxui::separator(),
                                                   ftxui::vbox({
                                                                       ftxui::paragraphAlignCenter("MIEJSCE PRZYLOTU: ") |
                                                                       ftxui::bold | color(ftxui::Color::SteelBlue3),
                                                                       ftxui::separator(),
                                                                       ftxui::paragraphAlignCenter(
                                                                               flightInfo.destination) | ftxui::bold |
                                                                       color(ftxui::Color::SteelBlue3),
                                                               }),
                                                   ftxui::separator(),
                                                   ftxui::vbox({
                                                                       ftxui::paragraphAlignCenter("CZAS WYLOTU: ") |
                                                                       ftxui::bold | color(ftxui::Color::Aquamarine3),
                                                                       ftxui::separator(),
                                                                       ftxui::paragraphAlignCenter(
                                                                               flightInfo.departureTime) | ftxui::bold |
                                                                       color(ftxui::Color::Aquamarine3),
                                                               }),
                                                   ftxui::separator(),
                                                   ftxui::vbox({
                                                                       ftxui::paragraphAlignCenter("MIEJSCE W SAMOLOCIE") |
                                                                       ftxui::bold | color(ftxui::Color::LightPink4),
                                                                       ftxui::separator(),
                                                                       ftxui::paragraphAlignCenter(placeInPlane) |
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
                                           }
            ) | ftxui::border;
            elements.push_back(window(ftxui::paragraphAlignCenter("BILET #" + std::to_string(flightInfo.flightNumber)), ticketContent));
        }
    }
    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter("TWOJE BILETY")}) |
                                           color(ftxui::Color::White),
                                           ftxui::separator(),
                                           ftxui::vbox(elements),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*createScreen()),
                                            ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;
}
