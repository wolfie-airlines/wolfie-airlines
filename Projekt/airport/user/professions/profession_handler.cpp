#include "profession_handler.h"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component_options.hpp"
#include <random>

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

bool guessDoctorQuestion(User& user) {
    auto collection = user.getSpecificCollection("doctor-question");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto&& doc : cursor) {
        documents.push_back(doc);
    }

    if (documents.empty()) {
        std::cerr << "Nie znaleziono żadnych pytań" << std::endl;
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, documents.size() - 1);

    int random_index = distrib(gen);
    std::string validAnswer = (std::string) documents[random_index]["answer"].get_string().value;
    std::string objawy = (std::string) documents[random_index]["question"].get_string().value;
    auto summary = [&] {
        auto content = ftxui::vbox({
                                           ftxui::hbox({ftxui::text(L"Zdiagnozuj poniższą chorobę na podstawie objaw:") | ftxui::bold}) | color(ftxui::Color::Orange4),
                                           ftxui::hbox({ftxui::text(objawy) | ftxui::bold}) | color(ftxui::Color::Orange3),
                                           ftxui::hbox({ftxui::text(L"Podpowiedź: Nazwa choroby jest zawsze jednym słowem.")  | ftxui::bold}) | color(ftxui::Color::YellowLight),
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
