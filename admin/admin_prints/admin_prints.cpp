#include <iostream>
#include "admin_prints.h"
#include "ftxui/dom/elements.hpp"

void DisplayAdminMenu() {
  auto summary = [&] {
      const auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" PANEL ADMINISTRATORA") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::text(L"1. Dodaj nowy lot   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"2. Dodaj nowe pytanie weryfikacyjne   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"3. Zarządzaj użytkownikami   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"4. Dodaj nowy przedmiot  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"5. Dodaj nowy lot  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"6. Usuń lot") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"7. Wyszukaj lot za pomocą ID") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"quit. Wyjdź z panelu administratora   ") | ftxui::bold})
                                       | color(ftxui::Color::DarkRed),
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
  Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}

void DisplayAddingFlightInfo() {
  auto summary = [&] {
      const auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L"UWAGA ADMINISTRATORZE!") | ftxui::bold})
                                       | color(ftxui::Color::YellowLight),
                                   ftxui::hbox({ftxui::text(L"Dodawanie lotu to nie lada bajka.")
                                                    | ftxui::bold}) | color(ftxui::Color::Orange3),
                                   ftxui::hbox({ftxui::text(
                                       L"Musisz podać wszystkie potrzebne informacje, aby lot mógł zostać dodany.")
                                                    | ftxui::bold}) | color(ftxui::Color::Orange1),
                                   ftxui::vbox({
                                                   ftxui::hbox({ftxui::text(L"POTRZEBNE INFORMACJE:") | ftxui::bold})
                                                       | color(ftxui::Color::BlueLight),
                                                   ftxui::hbox({
                                                                   ftxui::text(L"- ID LOTU ")
                                                                       | ftxui::bold | color(ftxui::Color::YellowLight),
                                                                   ftxui::paragraph(
                                                                       "(Unikalne ID lotu): konwencja nazewnictwa to: DWIE PIERWSZE LITERY MIASTA WYLOTU - DWIE PIERWSZE LITERY MIASTA PRZYLOTU)")
                                                                       | ftxui::bold | color(ftxui::Color::Yellow2),
                                                                   ftxui::text(
                                                                       " np. lot z Warszawy do Krakowa ma ID WA-KR")
                                                                       | ftxui::bold | color(ftxui::Color::SkyBlue1),
                                                               }),
                                                   ftxui::hbox({ftxui::text(L"- Miasto odlotu")
                                                                    | ftxui::bold}) | color(ftxui::Color::YellowLight),
                                                   ftxui::hbox({ftxui::text(
                                                       L"- Miasto przylotu") | ftxui::bold})
                                                       | color(ftxui::Color::YellowLight),
                                                   ftxui::hbox({
                                                                   ftxui::text(
                                                                       L"- Czas odlotu ")
                                                                       | color(ftxui::Color::YellowLight),
                                                                   ftxui::text(
                                                                       L"(format: DD.MM.YYYY HH:MM)")
                                                                       | color(ftxui::Color::Yellow2)
                                                                       | ftxui::bold}),
                                                   ftxui::hbox({
                                                                   ftxui::text(
                                                                       L"- Czas przylotu ")
                                                                       | color(ftxui::Color::YellowLight),
                                                                   ftxui::text(
                                                                       L"(format: DD.MM.YYYY HH:MM)")
                                                                       | color(ftxui::Color::Yellow2)
                                                                       | ftxui::bold}),
                                                   ftxui::hbox({
                                                                   ftxui::text(L"- Cena lotu ")
                                                                       | color(ftxui::Color::YellowLight),
                                                                   ftxui::text(L"(w PLN)")
                                                                       | color(ftxui::Color::Yellow2)
                                                                       | ftxui::bold}),
                                               }) | ftxui::border,
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"Jeśli chcesz przerwać dodawanie lotu wpisz:")
                                                    | ftxui::bold}) | color(ftxui::Color::RedLight),
                                   ftxui::hbox({ftxui::text(L"quit") | ftxui::bold}) | color(ftxui::Color::Red1),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"Jeśli chcesz kontynuować dodawanie lotu wpisz:")
                                                    | ftxui::bold}) | color(ftxui::Color::GreenLight),
                                   ftxui::hbox({ftxui::text(L"dalej") | ftxui::bold}) | color(ftxui::Color::Green1)
                               });
    return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
  };

  auto document = ftxui::vbox({summary()});

  document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 120);

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(document), ftxui::Dimension::Fit(document));
  Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}

std::string DisplayAdminMessageAndCaptureInput(const std::string &title_message, const std::string &text_message) {
  auto create_screen = [&] {
      const auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(title_message)})
                                       | color(ftxui::Color::White),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(text_message) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do panelu administratora.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::cin >> answer;

  return answer;
}

std::string DisplayAdminMessageAndCaptureLine(const std::string &title_message, const std::string &text_message) {
  auto create_screen = [&] {
      const auto summary = ftxui::vbox({
                                   ftxui::hbox({ftxui::paragraphAlignCenter(title_message)})
                                       | color(ftxui::Color::White),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(text_message) | ftxui::bold
                                                    | color(ftxui::Color::GrayLight)}),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(L"back. \U0001F519  Wróć do panelu administratora.")
                                                    | ftxui::color(ftxui::Color::CadetBlue) | ftxui::bold}),
                               });
    auto document = ftxui::vbox({window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), summary)});
    document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
    return std::make_shared<ftxui::Element>(document);
  };

  auto user_screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*create_screen()));
  Render(user_screen, *create_screen());
  std::cout << user_screen.ToString() << '\0' << std::endl;

  std::string answer;
  std::getline(std::cin >> std::ws, answer);

  return answer;
}

void DisplayManageUsersMenu() {
  auto summary = [&] {
      const auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" ZARZĄDZANIE UŻYTKOWNIKAMI") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::text(L"1. Zmień nazwę użytkownika wybranego użytkownika  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"2. Zmień adres e-mail wybranego użytkownika   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"3. Zmień zawód wybranego użytkownika   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"4. Zmień kartę premium wybranego użytkownika  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"5. Zmień typ zniżki wybranego użytkownika  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"6. Zmień zniżkę wybranego użytkownika (wartość zniżki)  ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"quit. Wróć do panelu administratora  ") | ftxui::bold})
                                       | color(ftxui::Color::DarkRed),
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
  Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}

void DisplaySerializeMenu() {
  auto summary = [&] {
      const auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" WYEKSPORTOWANE DANE LOTNICZE") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::text(L"Dane lotnicze zostały wyeksportowane do pliku \"flights.txt\".") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::separator(),
                                   ftxui::hbox({ftxui::text(
                                       L"Plik znajduje się w katalogu cmake-build-debug")
                                                    | ftxui::bold}) | color(ftxui::Color::YellowLight),
                               });
    return window(ftxui::paragraphAlignCenter("WOLFI AIRPORT ️ ✈"), content);
  };

  auto document = ftxui::vbox({summary()});

  document = document | size(ftxui::WIDTH, ftxui::LESS_THAN, 80);

  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
  Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}

