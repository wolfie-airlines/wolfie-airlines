#include "main_prints.h"
#include "../../user/user_functions/user_prints/user_prints.h"

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

void DisplayUserMenu(User &user) {

  auto summary = [&] {
    std::string username_and_title = user.username_;
    if (user.CheckIfAdmin()) {
      username_and_title += ", Administrator";
    }

    ftxui::Color username_color = ftxui::Color::GrayDark;
    if (user.CheckIfAdmin()) {
      username_color = ftxui::Color::Gold1;
    }
    auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::paragraphAlignRight("Zalogowano jako:")})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::paragraphAlignRight(username_and_title)})
                                       | color(username_color),
                                   ftxui::hbox({ftxui::text(L"1. Wyszukaj połączenie   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"2. Kup bilet na podróż   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"3. Zakup kartę premium   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"4. Zarządzaj ulgami   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"5. Moje bilety   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"6. Odprawa biletowa   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"7. Odprawa bagażowa   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"8. Panel administratora   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"profil. Przejdź do swojego profilu   ") | ftxui::bold})
                                       | color(ftxui::Color::CadetBlue),
                                   ftxui::hbox({ftxui::text(L"settings. Przejdź do ustawień   ") | ftxui::bold})
                                       | color(ftxui::Color::CadetBlue),
                                   ftxui::hbox({ftxui::text(L"logout. Wyloguj się   ") | ftxui::bold})
                                       | color(ftxui::Color::DarkRed),
                                   // ---------
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(
                                       L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:")
                                                    | ftxui::bold}) | color(ftxui::Color::YellowLight),
                               });

    return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
  };

  auto document = ftxui::vbox({summary()});

  document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

  auto
      user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
  ftxui::Render(user_screen, document);
  std::cout << user_screen.ToString() << '\0' << std::endl;
}

void DisplayMenu() {
  auto summary = [&] {
    auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" MENU UŻYTKOWNIKA") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::text(L"1. Zarejestruj się   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"2. Zaloguj się   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"3. Wyszukaj połączenie   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"4. Kup bilet na podróż   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"5. Odprawy online   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),

                                   ftxui::hbox({ftxui::text(L"quit. Zamknij aplikację   ") | ftxui::bold})
                                       | color(ftxui::Color::DarkRed),
                                   // ---------
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(
                                       L"Wprowadź akcję (bądź jej numer), którą chcesz wykonać poniżej:")
                                                    | ftxui::bold}) | color(ftxui::Color::YellowLight),
                               });
    return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
  };

  auto document = ftxui::vbox({summary()});

  document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}