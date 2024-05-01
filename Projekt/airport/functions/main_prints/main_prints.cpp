#include <iostream>
#include "main_prints.h"

void printScreen(const std::shared_ptr<ftxui::Element>& screen) {
    auto finalScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(*screen), ftxui::Dimension::Fit(*screen));
    ftxui::Render(finalScreen, *screen);
    std::cout << finalScreen.ToString() << '\0' << std::endl;
}

void printFullWidthScreen(std::shared_ptr<ftxui::Node> container) {
    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(container));
    ftxui::Render(userScreen, container);
    std::cout << userScreen.ToString() << '\0' << std::endl;
}

void printNodeScreen(std::shared_ptr<ftxui::Node> container) {
    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(container), ftxui::Dimension::Fit(container));
    ftxui::Render(userScreen, container);
    std::cout << userScreen.ToString() << '\0' << std::endl;
}

std::string displayMessageAndCaptureStringInput(const std::string& titleMessage, const std::string& textMessage) {
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

double displayMessageAndCaptureDoubleInput(const std::string& titleMessage, const std::string& textMessage) {
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

    double answer;
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
