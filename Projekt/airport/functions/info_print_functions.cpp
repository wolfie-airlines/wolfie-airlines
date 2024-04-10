#include <iostream>
#include "info_print_functions.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/util/ref.hpp"  // for Ref
#include "ftxui/screen/screen.hpp"

void validFunction(const std::string& titleMessage, const std::string& optionalMessage="") {
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

std::pair<std::string, std::string> login() {
    using namespace ftxui;
    std::string username;
    std::string password;

    Component input_username = Input(&username, "Twoja nazwa użytkownika");

    InputOption password_option;
    password_option.password = true;
    Component input_password = Input(&password, "Twoje hasło", password_option);
    auto screen = ScreenInteractive::TerminalOutput();

    auto component = Container::Vertical({
                                                 input_username,
                                                 input_password,
                                         });

    component |= CatchEvent([&](Event event) {
        if (event == Event::Return) {
            screen.Exit();
            return true;
        }
        return false;
    });

    auto renderer = Renderer(component, [&] {
        return vbox({
                            hbox(text("Nazwa użytkownika : "), input_username->Render()),
                            hbox(text("Hasło   : "), input_password->Render()),
                            separator(),
                    }) |
               border;
    });
    screen.Loop(renderer);

    return std::make_pair(username, password);
}

void logoutFunction() {
    ftxui::Element response;
    response = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"Wylogowano pomyślnie. Mamy nadzieję, że do zobaczenia niebawem!") | ftxui::bold}) | color(ftxui::Color::MagentaLight),
                           });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void seeyaFunction() {
    ftxui::Element response;
    response = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"Dziękujemy za skorzystanie z naszych usłuch, mamy nadzieję, że się podobało!") | ftxui::bold}) | color(ftxui::Color::MagentaLight),
                           });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto responseDocument = ftxui::vbox({response});
    auto responseScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(responseDocument));
    Render(responseScreen, responseDocument);
    std::cout << responseScreen.ToString() << '\0' << std::endl;
}

void errorFunction(const std::string& titleMessage, const std::string& optionalMessage="") {
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


