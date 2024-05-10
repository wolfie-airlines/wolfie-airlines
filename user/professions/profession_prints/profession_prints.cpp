#include "profession_prints.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

std::string DisplayProfessionInfo() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L"ATTENTION USER!") | ftxui::bold}) | color(ftxui::Color::Orange3),
            ftxui::hbox({ftxui::text(L"The choice of profession involves its verification.") | ftxui::bold}) | color(ftxui::Color::Orange4),
            ftxui::hbox({ftxui::text(
                             L"After verifying the genuineness of your profession, you will be ") |
                         ftxui::bold}) |
                color(ftxui::Color::BlueLight),
            ftxui::hbox({ftxui::text(
                             L"in the form of free transportation of the tools") |
                         ftxui::bold}) |
                color(ftxui::Color::BlueLight),
            ftxui::hbox({ftxui::text(L"needed for the job.") | ftxui::bold}) | color(ftxui::Color::BlueLight),
            ftxui::hbox({ftxui::text(
                             L"Items will not count towards the maximum possible weight to be taken in your luggage.") |
                         ftxui::bold}) |
                color(ftxui::Color::BlueLight),
            ftxui::hbox({ftxui::text(L"Don't cheat!") | ftxui::bold}) | color(ftxui::Color::Red1),

            ftxui::vbox({
                ftxui::hbox({ftxui::text(L"AVAILABLE OCCUPATIONS:") | ftxui::bold}) | color(ftxui::Color::SteelBlue),
                ftxui::hbox({ftxui::text(L"Musician (your hearing will be tested)") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                ftxui::hbox({ftxui::text(L"Doctor (your knowledge will be tested)") | ftxui::bold}) | color(ftxui::Color::GrayDark),
                ftxui::hbox({ftxui::text(
                                 L"Mathematician (your skills will be tested)") |
                             ftxui::bold}) |
                    color(ftxui::Color::GrayDark),
                ftxui::hbox({ftxui::text(
                                 L"Informatician (your skills will be tested)") |
                             ftxui::bold}) |
                    color(ftxui::Color::GrayDark),
                ftxui::hbox({ftxui::text(L"Policeman (badge number required)") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            }) | ftxui::border,
            ftxui::separator(),
            ftxui::hbox({ftxui::text(L"If you want to go to the profession selection enter:") | ftxui::bold}) | color(ftxui::Color::GrayDark),
            ftxui::hbox({ftxui::text(L"YES") | ftxui::bold}) | color(ftxui::Color::GreenYellow),
            ftxui::hbox({ftxui::text(
                             L"\U0001F519 In any other case, you will return to the main menu.") |
                         ftxui::bold}) |
                color(ftxui::Color::DarkSeaGreen),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    std::cout << screen.ToString() << '\0' << std::endl;
    std::string option;
    std::cin >> option;
    return option;
}

int CreateProfessionScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    int selected = 0;
    std::vector<std::string> entries = {
        "I am a musician (requires confirmation)",
        "I am a doctor (requires confirmation)",
        "I am a mathematician (requires confirmation)",
        "I am an informatician (requires confirmation)",
        "I am a police officer (requires confirmation)",
        "\U0001F519 Return to main menu",
    };

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

void ValidAnswer(const std::string &category, User &user) {
    std::string odmiana;
    bool is_police = false;
    if (category == "music") {
        odmiana = "musicians";
    } else if (category == "doctor") {
        odmiana = "doctors";
    } else if (category == "mathmetician") {
        odmiana = "mathmeticians";
    } else if (category == "informatician") {
        odmiana = "informaticians";
    } else if (category == "policeman") {
        odmiana = "police";
        is_police = true;
    }

    auto summary = [&] {
        auto content = ftxui::vbox({
            is_police ? ftxui::hbox({ftxui::text(L"Welcome officer!") | ftxui::bold}) | color(ftxui::Color::Green) : ftxui::hbox({ftxui::text(L"Exactly! This is the correct answer!") | ftxui::bold}) | color(ftxui::Color::Green),
            ftxui::hbox({ftxui::text("Discounts for " + odmiana + " were awarded!") | ftxui::bold}) | color(ftxui::Color::YellowLight),
            ftxui::hbox({ftxui::text(L"You will see them in your profile.") | ftxui::bold}) | color(ftxui::Color::BlueLight),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);

    user.UpdateUserInDatabase("profession", category);
    user.profession_ = category;

    std::cout << screen.ToString() << '\0' << std::endl;
}

void InvalidAnswer() {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L"Unfortunately, your answer is not correct....") | ftxui::bold}) | color(ftxui::Color::Red),
            ftxui::hbox({ftxui::text(L"You can always try again.") | ftxui::bold}) | color(ftxui::Color::Orange1),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(screen, document);
    std::cout << screen.ToString() << '\0' << std::endl;
}