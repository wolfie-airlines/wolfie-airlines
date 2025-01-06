#include "profession_handler.h"

#include <iomanip>
#include <random>
#include <variant>

#include "ftxui/component/component_options.hpp"

template<typename T>
bool AreEqualWithTolerance(T a, T b, T tolerance = std::numeric_limits<T>::epsilon()) {
  return std::abs(a - b) < tolerance;
}

bool GuessMusicAuthor(const std::string &music_link) {
  std::string valid_answer;
  if (music_link == "sinatra") {
    valid_answer = "Sinatra";
  } else if (music_link == "acdc") {
    valid_answer = "AC/DC";
  } else if (music_link == "beethoven") {
    valid_answer = "Beethoven";
  } else if (music_link == "vacations") {
    valid_answer = "Vacations";
  } else if (music_link == "vivaldi") {
    valid_answer = "Vivaldi";
  } else if (music_link == "youngboy") {
    valid_answer = "Youngboy";
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

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::cin >> answer;
  return answer == valid_answer;
}

bool GuessDoctorQuestion(User &user) {
  auto collection = user.GetSpecificCollection("doctor-question");
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
  std::string valid_answer = (std::string) documents[random_index]["answer"].get_string().value;
  std::string question = (std::string) documents[random_index]["question"].get_string().value;
  auto summary = [&] {
    auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(
                                       L"Zdiagnozuj poniższą chorobę na podstawie objaw:") |
                                       ftxui::bold}) |
                                       color(ftxui::Color::Orange4),
                                   ftxui::hbox({ftxui::text(question) | ftxui::bold}) |
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

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
  std::string answer;
  std::cin >> answer;
  return answer == valid_answer;
}

bool GuessInformaticQuestion(User &user) {
  auto collection = user.GetSpecificCollection("informatic-questions");
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
  int random_index = distrib(gen);

  std::string language = (std::string) questions[random_index]["language"].get_string().value;
  std::string error = (std::string) questions[random_index]["error"].get_string().value;
  auto code = ftxui::vbox();
  std::string code_string = (std::string) questions[random_index]["code"].get_string().value;
  std::istringstream code_stream(code_string);
  std::string line;

  int line_number = 1;
  while (std::getline(code_stream, line, ',')) {
    auto line_number_text = ftxui::text(std::to_string(line_number) + ". ") | color(ftxui::Color::BlueLight);
    auto code_line = ftxui::text(line) | color(ftxui::Color::NavajoWhite1);
    auto numbered_line = ftxui::hbox(std::move(line_number_text), std::move(code_line));
    code = ftxui::vbox(std::move(code), std::move(numbered_line));
    line_number++;
  }

  auto question_to_user = ftxui::text(L"W której linijce kodu znajduje się problem?");
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
                                   question_to_user | color(ftxui::Color::BlueLight),
                               });

  auto window = ftxui::window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), std::move(container));

  window = window | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(window), ftxui::Dimension::Fit(window));

  ftxui::Render(screen, window);
  std::cout << screen.ToString() << '\0' << std::endl;

  int answer;
  std::cin >> answer;

  return answer == questions[random_index]["answer"].get_int32().value;
}

bool GuessMathQuestion(User &user) {
  auto collection = user.GetSpecificCollection("math-questions");
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
  int random_index = distrib(gen);

  std::string topic = (std::string) questions[random_index]["problem"].get_string().value;
  std::string description = (std::string) questions[random_index]["description"].get_string().value;
  std::string hint = (std::string) questions[random_index]["hint"].get_string().value;
  bsoncxx::types::bson_value::view solution_value = questions[random_index]["solution"].get_value();
  std::string answer;
  std::string solution;

  if (solution_value.type() == bsoncxx::type::k_int32) {
    solution = std::to_string(solution_value.get_int32().value);
  } else if (solution_value.type() == bsoncxx::type::k_double) {
    solution = std::to_string(solution_value.get_double().value);
  } else if (solution_value.type() == bsoncxx::type::k_string) {
    solution = static_cast<std::string>(solution_value.get_string().value);
  } else {
    std::cerr << "Nieznany typ rozwiązania" << std::endl;
    return false;
  }

  auto whole_problem = ftxui::vbox();
  std::istringstream istringstream(description);
  std::string line;
  while (std::getline(istringstream, line, ',')) {
    auto problem_line = ftxui::text(line) | color(ftxui::Color::NavajoWhite1);
    whole_problem = ftxui::vbox(std::move(whole_problem), std::move(problem_line));
  }

  auto container = ftxui::vbox({
                                   ftxui::hbox({ftxui::text("Zadanie z działu: " + topic) | ftxui::bold})
                                       | color(ftxui::Color::YellowLight),
                                   ftxui::separator(),
                                   whole_problem | ftxui::border,
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text("Podpowiedź: ") | ftxui::bold})
                                       | color(ftxui::Color::BlueLight),
                                   ftxui::hbox({ftxui::text(hint) | ftxui::bold}) | color(ftxui::Color::Blue),
                               });

  auto window = ftxui::window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), std::move(container));

  window = window | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(window), ftxui::Dimension::Fit(window));

  ftxui::Render(screen, window);
  std::cout << screen.ToString() << '\0' << std::endl;

  std::cin >> answer;

  if (solution_value.type() == bsoncxx::type::k_double) {
    return AreEqualWithTolerance(std::stod(solution), std::stod(answer));
  } else {
    return answer == solution;
  }
}

bool DisplayPoliceProfession() {
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
  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;

  int badge_number;
  std::cin >> badge_number;

  if (badge_number < 100000 || badge_number > 999999) {
    return false;
  }

  return badge_number != 123456;
}
