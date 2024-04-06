#include "profession_prints.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/component.hpp"
#include "../../User.h"

std::string displayProfessionInfo() {
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L"UWAGA UŻYTKOWNIKU!") | ftxui::bold}) | color(ftxui::Color::Orange3),
                                           ftxui::hbox({ftxui::text(L"Wybór zawodu wiąże się z jego weryfikacją.") | ftxui::bold}) | color(ftxui::Color::Orange4),
                                           ftxui::hbox({ftxui::text(L"Po zweryfikowaniu prawdziwości wykonywanego przez Ciebie zawodu, będzie")  | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                           ftxui::hbox({ftxui::text(L"przysługiwała Ci zniżka w postaci darmowego przewozu potrzebnych do danej")  | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                           ftxui::hbox({ftxui::text(L"pracy narzędzi.")  | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                           ftxui::hbox({ftxui::text(L"Nie oszukuj!")  | ftxui::bold}) | color(ftxui::Color::Red1),

                                           ftxui::vbox({
                                                ftxui::hbox({ftxui::text(L"DOSTĘPNE ZAWODY:")  | ftxui::bold}) | color(ftxui::Color::SteelBlue),
                                                ftxui::hbox({ftxui::text(L"Muzyk (testowany będzie Twój słuch)")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                                ftxui::hbox({ftxui::text(L"Lekarz (testowana będzie Twoja wiedza)")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                                ftxui::hbox({ftxui::text(L"Sportowiec (piłkarz/atleta/koszykarz) (testowana będzie Twoja wiedza)")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                                ftxui::hbox({ftxui::text(L"Jestem matematykiem (testowane będą Twoje umiejętności)")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                                ftxui::hbox({ftxui::text(L"Jestem informatykiem (testowane będą Twoje umiejętności)")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           }) | ftxui::border,
                                           ftxui::separator(),
                                           ftxui::hbox({ftxui::text(L"Jeśli chcesz przejść do wyboru zawodu wpisz:")  | ftxui::bold}) | color(ftxui::Color::GrayDark),
                                           ftxui::hbox({ftxui::text(L"TAK")  | ftxui::bold}) | color(ftxui::Color::GreenYellow),
                                           ftxui::hbox({ftxui::text("W każdym innym wypadku wrócisz do menu głównego.")  | ftxui::bold}) | color(ftxui::Color::DarkSeaGreen),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);
    std::cout << userScreen.ToString() << '\0' << std::endl;
    std::string option;
    std::cin >> option;
    return option;
}

int CreateProfessionScreen() {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    int selected = 0;
    std::vector<std::string> entries = {
            "Jestem muzykiem (wymaga potwierdzenia)",
            "Jestem lekarzem (wymaga potwierdzenia)",
            "Jestem sportowcem (piłkarz/atleta/koszykarz) (wymaga potwierdzenia)",
            "Jestem matematykiem (wymaga potwierdzenia)",
            "Jestem informatykiem (wymaga potwierdzenia)",
            "↩️ Wróć do menu głównego",
    };

    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&entries, &selected, option);

    screen.Loop(menu);
    return selected;
}

bool guessMusicAuthor(const std::string& musicLink) {
    std::string validAnswer;
    if(musicLink == "sinatra") {
        validAnswer = "Sinatra";
    } else if(musicLink == "acdc") {
        validAnswer = "AC/DC";
    } else if(musicLink == "beethoven") {
        validAnswer = "Beethoven";
    } else if(musicLink == "vacations") {
        validAnswer = "Vacations";
    } else if(musicLink == "vivaldi") {
        validAnswer = "Vivaldi";
    } else if(musicLink == "youngboy") {
        validAnswer = "Youngboy";
    } else {
        return "Nieznany wykonawca";
    }
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L"Jaki wykonawca/zespół stworzył ten utwór?") | ftxui::bold}) | color(ftxui::Color::Orange4),
                                           ftxui::hbox({ftxui::text(L"W przypadku wykonawcy podaj jedynie jego nazwisko.") | ftxui::bold}) | color(ftxui::Color::Orange3),
                                           ftxui::hbox({ftxui::text(L"Odpowiedź wprowadź poniżej")  | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::string userAnswer;
    std::cin >> userAnswer;
    return userAnswer == validAnswer;
}

void validAnswer(const std::string& category, User& user) {
    std::string odmiana;
    if(category == "muzyk") {
        odmiana = "muzyków";
    } else if (category == "lekarz") {
        odmiana = "lekarzy";
    } else if (category == "sportowiec") {
        odmiana = "sportowców";
    } else if (category == "matematyk") {
        odmiana = "matematyków";
    } else if (category == "informatyk") {
        odmiana = "informatyków";
    }

    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L"Dokładnie! To poprawna odpowiedź!") | ftxui::bold}) | color(ftxui::Color::Green),
                                           ftxui::hbox({ftxui::text("Zniżki dla " + odmiana + " zostały przyznane!") | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                           ftxui::hbox({ftxui::text(L"Zobaczysz je w swoim profilu.")  | ftxui::bold}) | color(ftxui::Color::BlueLight),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);


    // user.addDiscount(category);
    // aktualizacja obiektu użytkownika w bazie danych
    

    std::cout << userScreen.ToString() << '\0' << std::endl;
}

void invalidAnswer() {
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L"Niestety, Twoja odpowiedź nie jest poprawna...") | ftxui::bold}) | color(ftxui::Color::Red),
                                           ftxui::hbox({ftxui::text(L"Możesz zawsze spróbować ponownie.")  | ftxui::bold}) | color(ftxui::Color::Orange1),
                                   });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});

    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);
    std::cout << userScreen.ToString() << '\0' << std::endl;
}