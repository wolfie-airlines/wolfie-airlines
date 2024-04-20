#include "tickets_print_functions.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/component.hpp"
#include "../../user/User.h"
#include "qrcodegen.hpp"
#include "../../qr-code/qrcode_prints.h"

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

bool validChoice(const std::string& choiceTitle, const std::string& choiceText) {
    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter(choiceTitle)}) | color(ftxui::Color::GrayDark),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text(choiceText) | ftxui::bold | color(ftxui::Color::Green)}),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string answer;
    std::cin >> answer;

    if(answer == "tak" || answer == "Tak" || answer == "TAK") return true;
    else return false;
}

std::string displayMessageAndCaptureInput(const std::string& titleMessage, const std::string& textMessage) {
    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter(titleMessage)}) | color(ftxui::Color::White),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text(textMessage) | ftxui::bold | color(ftxui::Color::GrayLight)}),
                                           ftxui::separator(),
                                           ftxui::hbox({ ftxui::text(L"back. \U0001F519  Wróć do głównego menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold }),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string answer;
    std::cin >> answer;

    return answer;
}

std::string displayWarningAndCaptureInput(const std::string& titleMessage, const std::string& textMessage) {
    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter(titleMessage)}) | color(ftxui::Color::Red),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::text(textMessage) | ftxui::bold | color(ftxui::Color::RedLight)}),
                                           ftxui::separator(),
                                           ftxui::hbox({ ftxui::text(L"back. \U0001F519  Wróć do głównego menu.") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold }),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string answer;
    std::cin >> answer;

    return answer;
}


void druknijFakturke(
        User& user, FlightConnection& foundConnection, const std::vector<int>& selectedSeats
        ) {

    time_t now = time(nullptr);
    tm ltm{};
    localtime_s(&ltm, &now);
    std::string date = std::to_string(1900 + ltm.tm_year) + "-" + std::to_string(1 + ltm.tm_mon) + "-" + std::to_string(ltm.tm_mday);


    std::string totalPrice = std::to_string(foundConnection.getPrice() * selectedSeats.size());
    std::string howMuchDiscount = std::to_string(foundConnection.getPrice() * selectedSeats.size() - foundConnection.getPrice() * selectedSeats.size() * user.discount);
    std::string targetPrice = std::to_string(foundConnection.getPrice() * selectedSeats.size() * user.discount);

    ftxui::Elements elements;
    for (const auto& ticket : selectedSeats) {
        std::string row = std::to_string(ticket % 9 == 0 ? ticket / 9 : ticket / 9 + 1);
        std::string seat = std::to_string(ticket % 9 == 0 ? 9 : ticket % 9);
        std::string placeInPlane = "Rząd: ";
        placeInPlane += row;
        placeInPlane += ", Miejsce: ";
        placeInPlane += seat;
        elements.push_back(ftxui::hbox({
                                                ftxui::paragraphAlignLeft("ID LOTU: " + foundConnection.getIdentifier()) | ftxui::bold | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft("MIEJSCE ODLOTU: " + foundConnection.getDepartureCity()) | ftxui::bold | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft("MIEJSCE PRZYLOTU: " + foundConnection.getDestinationCity()) | ftxui::bold | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft("CZAS WYLOTU: " + foundConnection.getDepartureTime()) | ftxui::bold | color(ftxui::Color::GrayLight),
                                                ftxui::paragraphAlignLeft(placeInPlane) | ftxui::bold | color(ftxui::Color::GrayLight),
                                        }) | ftxui::border);
    }

    auto createScreen = [&] {
        auto summary = ftxui::vbox({
                                           ftxui::hbox({ftxui::paragraphAlignCenter("POTWIERDZENIE ZAKUPU BILETÓW")}) | color(ftxui::Color::White),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                               ftxui::paragraphAlignLeft("Data: " + date)  | ftxui::bold | color(ftxui::Color::GrayLight),
                                                               ftxui::paragraphAlignLeft("E-mail: " + user.email)  | ftxui::bold | color(ftxui::Color::GrayLight),
                                                               ftxui::paragraphAlignLeft("Użytkownik: " + user.username)  | ftxui::bold | color(ftxui::Color::GrayLight)
                                           }),
                                           ftxui::separator(),
                                           ftxui::vbox(elements),
                                           ftxui::separator(),
                                           ftxui::hbox({
                                                                ftxui::paragraphAlignRight("Cena: " + totalPrice + " PLN") | ftxui::bold | color(ftxui::Color::Gold3),
                                                                ftxui::paragraphAlignRight("Zniżka: " + howMuchDiscount + " PLN") | ftxui::bold | color(ftxui::Color::SteelBlue1),
                                                                ftxui::paragraphAlignRight("Do zapłaty: " + targetPrice + " PLN") | ftxui::bold | color(ftxui::Color::Gold1)
                                           }),
                                           ftxui::hbox({ ftxui::text(L"ODPRAW SIĘ ONLINE JUŻ TERAZ! Zeskanuj kod poniżej:") | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold }),
                                   });
        auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
        document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return std::make_shared<ftxui::Element>(document);
    };

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*createScreen()));
    ftxui::Render(userScreen, *createScreen());
    std::cout << userScreen.ToString() << '\0' << std::endl;
    createQR(user.email, user.username, foundConnection.getIdentifier(), selectedSeats);
}