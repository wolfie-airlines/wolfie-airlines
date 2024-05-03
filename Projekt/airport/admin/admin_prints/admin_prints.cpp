#include <iostream>
#include "admin_prints.h"
#include "ftxui/dom/elements.hpp"

void DisplayAdminMenu() {
  auto summary = [&] {
    auto content = ftxui::vbox({
                                   ftxui::hbox({ftxui::text(L" PANEL ADMINISTRATORA") | ftxui::bold})
                                       | color(ftxui::Color::Blue),
                                   ftxui::hbox({ftxui::text(L"1. Dodaj nowy lot   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"2. Dodaj nowe pytanie weryfikacyjne   ") | ftxui::bold})
                                       | color(ftxui::Color::GrayDark),
                                   ftxui::hbox({ftxui::text(L"3. Zarządzaj użytkownikami   ") | ftxui::bold})
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
  ftxui::Render(screen, document);
  std::cout << screen.ToString() << '\0' << std::endl;
}


