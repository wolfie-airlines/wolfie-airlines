#include "profession_handler.h"

#include <iomanip>
#include <random>
#include <variant>

#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

template <typename T>
bool areEqualWithTolerance(T a, T b, T tolerance = std::numeric_limits<T>::epsilon()) {
    return std::abs(a - b) < tolerance;
}

bool guessMusicAuthor(const std::string &musicLink) {
    std::string validAnswer;
    if (musicLink == "sinatra") {
        validAnswer = "Sinatra";
    } else if (musicLink == "acdc") {
        validAnswer = "AC/DC";
    } else if (musicLink == "beethoven") {
        validAnswer = "Beethoven";
    } else if (musicLink == "vacations") {
        validAnswer = "Vacations";
    } else if (musicLink == "vivaldi") {
        validAnswer = "Vivaldi";
    } else if (musicLink == "youngboy") {
        validAnswer = "Youngboy";
    } else {
        return "Nieznany wykonawca";
    }
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(
                             L"Jaki wykonawca/zespół stworzył ten utwór?") |
                         ftxui::bold}) |
                color(ftxui::Color::Orange4),
            ftxui::hbox({ftxui::text(
                             L"W przypadku wykonawcy podaj jedynie jego nazwisko.") |
                         ftxui::bold}) |
                color(ftxui::Color::Orange3),
            ftxui::hbox({ftxui::text(L"Odpowiedź wprowadź poniżej") | ftxui::bold}) |
                color(ftxui::Color::BlueLight),
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

bool guessDoctorQuestion(User &user) {
    auto collection = user.getSpecificCollection("doctor-question");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> documents;
    for (auto &&doc : cursor) {
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
    std::string validAnswer = (std::string)documents[random_index]["answer"].get_string().value;
    std::string objawy = (std::string)documents[random_index]["question"].get_string().value;
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(
                             L"Zdiagnozuj poniższą chorobę na podstawie objaw:") |
                         ftxui::bold}) |
                color(ftxui::Color::Orange4),
            ftxui::hbox({ftxui::text(objawy) | ftxui::bold}) |
                color(ftxui::Color::Orange3),
            ftxui::hbox({ftxui::text(
                             L"Podpowiedź: Nazwa choroby jest zawsze jednym słowem.") |
                         ftxui::bold}) |
                color(ftxui::Color::YellowLight),
            ftxui::hbox({ftxui::text(L"Odpowiedź wprowadź poniżej") | ftxui::bold}) |
                color(ftxui::Color::BlueLight),
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

bool guessInformaticQuestion(User &user) {
    auto collection = user.getSpecificCollection("informatic-questions");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> questions;
    for (auto &&doc : cursor) {
        questions.push_back(doc);
    }

    if (questions.empty()) {
        std::cerr << "Nie znaleziono żadnych pytań" << std::endl;
        return false;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, questions.size() - 1);
    int randomIndex = distrib(gen);

    std::string language = (std::string)questions[randomIndex]["language"].get_string().value;
    std::string error = (std::string)questions[randomIndex]["error"].get_string().value;
    auto code = ftxui::vbox();
    std::string codeString = (std::string)questions[randomIndex]["code"].get_string().value;
    std::istringstream codeStream(codeString);
    std::string line;
    int lineNumber = 1;
    while (std::getline(codeStream, line, ',')) {
        auto lineNumberText = ftxui::text(std::to_string(lineNumber) + ". ") | color(ftxui::Color::BlueLight);
        auto codeLine = ftxui::text(line) | color(ftxui::Color::NavajoWhite1);
        auto numberedLine = ftxui::hbox(std::move(lineNumberText), std::move(codeLine));
        code = ftxui::vbox(std::move(code), std::move(numberedLine));
        lineNumber++;
    }
    auto answer = ftxui::text(L"W której linijce kodu znajduje się problem?");

    auto container = ftxui::vbox({
        ftxui::hbox({ftxui::text("Język programowania: " + language) | ftxui::bold}) |
            color(ftxui::Color::YellowLight),
        ftxui::separator(),
        code | ftxui::border,
        ftxui::separator(),
        ftxui::hbox({ftxui::text("Błąd w wyświetlonym kodzie: ") | ftxui::bold}) |
            color(ftxui::Color::IndianRed),
        ftxui::hbox({ftxui::text(error) | ftxui::bold}) | color(ftxui::Color::Red),
        ftxui::separator(),
        answer | color(ftxui::Color::BlueLight),
    });

    auto window = ftxui::window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), std::move(container));

    window = window | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(window), ftxui::Dimension::Fit(window));

    ftxui::Render(userScreen, window);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    int userAnswer;
    std::cin >> userAnswer;

    return userAnswer == questions[randomIndex]["answer"].get_int32().value;
}

bool guessMathQuestion(User &user) {
    auto collection = user.getSpecificCollection("math-questions");
    auto cursor = collection.find({});
    std::vector<bsoncxx::document::view> questions;
    for (auto &&doc : cursor) {
        questions.push_back(doc);
    }

    if (questions.empty()) {
        std::cerr << "Nie znaleziono żadnych pytań" << std::endl;
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, questions.size() - 1);
    int randomIndex = distrib(gen);

    std::string topic = (std::string)questions[randomIndex]["problem"].get_string().value;
    std::string description = (std::string)questions[randomIndex]["description"].get_string().value;
    std::string hint = (std::string)questions[randomIndex]["hint"].get_string().value;
    bsoncxx::types::bson_value::view solutionValue = questions[randomIndex]["solution"].get_value();
    std::string userAnswer;
    std::string solution;

    if (solutionValue.type() == bsoncxx::type::k_int32) {
        solution = std::to_string(solutionValue.get_int32().value);
    } else if (solutionValue.type() == bsoncxx::type::k_double) {
        solution = std::to_string(solutionValue.get_double().value);
    } else if (solutionValue.type() == bsoncxx::type::k_utf8) {
        solution = solutionValue.get_string().value;
    } else {
        std::cerr << "Nieznany typ rozwiązania" << std::endl;
        return false;
    }

    auto wholeProblem = ftxui::vbox();
    std::istringstream problemStream(description);
    std::string line;
    while (std::getline(problemStream, line, ',')) {
        auto problemLine = ftxui::text(line) | color(ftxui::Color::NavajoWhite1);
        wholeProblem = ftxui::vbox(std::move(wholeProblem), std::move(problemLine));
    }

    auto container = ftxui::vbox({
        ftxui::hbox({ftxui::text("Zadanie z działu: " + topic) | ftxui::bold}) | color(ftxui::Color::YellowLight),
        ftxui::separator(),
        wholeProblem | ftxui::border,
        ftxui::separator(),
        ftxui::hbox({ftxui::text("Podpowiedź: ") | ftxui::bold}) | color(ftxui::Color::BlueLight),
        ftxui::hbox({ftxui::text(hint) | ftxui::bold}) | color(ftxui::Color::Blue),
    });

    auto window = ftxui::window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), std::move(container));

    window = window | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(window), ftxui::Dimension::Fit(window));

    ftxui::Render(userScreen, window);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    std::cin >> userAnswer;

    // Printy testowe, TODO: wyrzucić potem
    std::cout << "Rozwiazanie: " << solution << std::endl;
    std::cout << "Odpowiedz uzytkownika: " << userAnswer << std::endl;

    if (solutionValue.type() == bsoncxx::type::k_double) {
        return areEqualWithTolerance(std::stod(solution), std::stod(userAnswer));
    } else {
        return userAnswer == solution;
    }
}

bool displayPoliceProfession(User &user) {
    auto summary = [&] {
        auto content = ftxui::vbox({
            ftxui::hbox({ftxui::text(L"Sprawdźmy Cię funkcjonariuszu") | ftxui::bold}) |
                color(ftxui::Color::YellowLight),
            ftxui::hbox({ftxui::text(L"Wpisz swój numer odznaki") | ftxui::bold}) |
                color(ftxui::Color::White),
        });
        return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
    };

    auto document = ftxui::vbox({summary()});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    auto userScreen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
    ftxui::Render(userScreen, document);
    std::cout << userScreen.ToString() << '\0' << std::endl;

    int badgeNumber;
    std::cin >> badgeNumber;

    if (badgeNumber < 100000 || badgeNumber > 999999) {
        return false;
    }

    return badgeNumber != 123456;
}
