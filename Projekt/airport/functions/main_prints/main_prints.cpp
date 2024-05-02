#include "main_prints.h"

#include <iostream>

void PrintScreen(const std::shared_ptr<ftxui::Element> &screen) {
  auto final_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(*screen), ftxui::Dimension::Fit(*screen));
  ftxui::Render(final_screen, *screen);
  std::cout << final_screen.ToString() << '\0' << std::endl;
}

void PrintFullWidthScreen(std::shared_ptr<ftxui::Node> container) {
  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(container));
  ftxui::Render(user_screen, container);
  std::cout << user_screen.ToString() << '\0' << std::endl;
}

void PrintNodeScreen(std::shared_ptr<ftxui::Node> container) {
  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Fit(container), ftxui::Dimension::Fit(container));
  ftxui::Render(user_screen, container);
  std::cout << user_screen.ToString() << '\0' << std::endl;
}

std::string DisplayMessageAndCaptureStringInput(const std::string &title_message, const std::string &text_message) {
  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(title_message)})
                                       | color(ftxui::Color::White),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(text_message) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do głównego menu.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::cin >> answer;

  return answer;
}

double DisplayMessageAndCaptureDoubleInput(const std::string &title_message, const std::string &text_message) {
  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(title_message)})
                                       | color(ftxui::Color::White),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(text_message) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do głównego menu.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  double answer;
  std::cin >> answer;

  return answer;
}

std::string DisplayWarningAndCaptureInput(const std::string &title_message, const std::string &text_message) {
  auto create_screen = [&] {
    auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(title_message)}) | color(ftxui::Color::Red),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(text_message) | ftxui::bold
                                                    | color(ftxui::Color::RedLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do głównego menu.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  ftxui::Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::cin >> answer;

  return answer;
}
