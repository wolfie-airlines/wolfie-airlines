#include "info_prints.h"

#include <iostream>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/util/ref.hpp"

void PrintSuccessMessage(const std::string &title_message, const std::string &optional_message = "") {
    ftxui::Element response;
    if (optional_message.empty()) {
        response = ftxui::vbox({
            ftxui::hbox({ftxui::text(title_message) | ftxui::bold}) | color(ftxui::Color::Green),
        });
    } else {
        response = ftxui::vbox({
            ftxui::hbox({ftxui::text(title_message) | ftxui::bold}) | color(ftxui::Color::Green),
            ftxui::hbox({ftxui::text(optional_message) | ftxui::bold}) | color(ftxui::Color::CyanLight),
        });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto response_document = ftxui::vbox({response});
    auto response_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(response_document));
    Render(response_screen, response_document);
    std::cout << response_screen.ToString() << '\0' << std::endl;
}

void PrintLogout(User &user) {
    ftxui::Element response;
    response = ftxui::vbox({
        ftxui::hbox({ftxui::text(L"Logged out successfully. We hope to see you soon!") | ftxui::bold}) | color(ftxui::Color::MagentaLight),
    });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto response_document = ftxui::vbox({response});
    auto response_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(response_document));
    Render(response_screen, response_document);
    std::cout << response_screen.ToString() << '\0' << std::endl;
    user.Reset();
}

void PrintSeeya() {
    ftxui::Element response;
    response = ftxui::vbox({
        ftxui::hbox({ftxui::text(
                         L"Thank you for using our services, we hope you enjoyed it!") |
                     ftxui::bold}) |
            color(ftxui::Color::MagentaLight),
    });
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto response_document = ftxui::vbox({response});
    auto response_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(response_document));
    Render(response_screen, response_document);
    std::cout << response_screen.ToString() << '\0' << std::endl;
}

void PrintErrorMessage(const std::string &title_message, const std::string &optional_message = "") {
    ftxui::Element response;
    if (optional_message.empty()) {
        response = ftxui::vbox({
            ftxui::hbox({ftxui::text(title_message) | ftxui::bold}) | color(ftxui::Color::Red),
        });
    } else {
        response = ftxui::vbox({
            ftxui::hbox({ftxui::text(title_message) | ftxui::bold}) | color(ftxui::Color::Red),
            ftxui::hbox({ftxui::text(optional_message) | ftxui::bold}) | color(ftxui::Color::Orange1),
        });
    }
    response = response | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto response_document = ftxui::vbox({response});
    auto response_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(response_document));
    Render(response_screen, response_document);
    std::cout << response_screen.ToString() << '\0' << std::endl;
}
