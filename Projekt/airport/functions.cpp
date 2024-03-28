#include <iostream>
#include "functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"

void validFunction(const std::string& titleMessage, const std::string& optionalMessage) {
    ftxui::Element response;
    if(optionalMessage.empty()) {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Green),
                               });
    } else {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Green),
                                       ftxui::hbox({ftxui::text(optionalMessage) | ftxui::bold}) | color(ftxui::Color::CyanLight),
                               });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void errorFunction(const std::string& titleMessage, const std::string& optionalMessage) {
    ftxui::Element response;
    if(optionalMessage.empty()) {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Red),
                               });
    } else {
        response = ftxui::vbox({
                                       ftxui::hbox({ftxui::text(titleMessage) | ftxui::bold}) | color(ftxui::Color::Red),
                                       ftxui::hbox({ftxui::text(optionalMessage) | ftxui::bold}) | color(ftxui::Color::Orange1),
                               });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}
