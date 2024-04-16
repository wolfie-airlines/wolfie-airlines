#include "tickets_print_functions.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/component.hpp"

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