#include "user_authentication.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

std::tuple<std::string, std::string, std::string, bool> RegisterUser() {
  using namespace ftxui;
  std::string username;
  std::string email;
  std::string password;
  bool cancelled = false;

  Component input_username = Input(&username, "Twoja wybrana nazwa użytkownika");

  Component input_email = Input(&email, "Twój adres e-mail");

  InputOption password_option;
  password_option.password = true;
  Component input_password = Input(&password, "Hasło", password_option);
  auto screen = ScreenInteractive::TerminalOutput();

  auto component = Container::Vertical({
                                           input_username,
                                           input_email,
                                           input_password,
                                       });

  component |= CatchEvent([&](const Event &event) {
    if (event == Event::Escape) {
      screen.Exit();
      cancelled = true;
      return true;
    } else if (event == Event::Return) {
      screen.Exit();
      return true;
    }
    return false;
  });

  auto renderer = Renderer(component, [&] {
    return vbox({
                    hbox(text("Nazwa użytkownika : "), input_username->Render()),
                    hbox(text("Email             : "), input_email->Render()),
                    hbox(text("Hasło             : "), input_password->Render()),
                    separator(),
                    hbox(text("W celu zatwierdzenia kliknij klawisz Enter") | bold | color(Color::YellowLight)),
                    hbox(text("Jeśli chcesz anulować kliknij klawisz Escape") | bold | color(Color::RedLight)),
                }) |
        border;
  });
  screen.Loop(renderer);

  return std::make_tuple(username, email, password, cancelled);
}

std::tuple<std::string, std::string, bool> Login() {
  using namespace ftxui;
  std::string username;
  std::string password;
  bool cancelled = false;

  Component input_username = Input(&username, "Twoja nazwa użytkownika");

  InputOption password_option;
  password_option.password = true;
  Component input_password = Input(&password, "Twoje hasło", password_option);
  auto screen = ScreenInteractive::TerminalOutput();

  auto component = Container::Vertical({
                                           input_username,
                                           input_password,
                                       });

  component |= CatchEvent([&](const Event &event) {
    if (event == Event::Escape) {
      screen.Exit();
      cancelled = true;
      return true;
    } else if (event == Event::Return) {
      screen.Exit();
      return true;
    }
    return false;
  });

  auto renderer = Renderer(component, [&] {
    return vbox({
                    hbox(text("Nazwa użytkownika : "), input_username->Render()),
                    hbox(text("Hasło   : "), input_password->Render()),
                    separator(),
                    hbox(text("W celu zatwierdzenia kliknij ENTER") | bold | color(Color::YellowLight)),
                    hbox(text("Jeśli chcesz anulować kliknij klawisz Escape") | bold | color(Color::RedLight)),
                }) |
        border;
  });
  screen.Loop(renderer);

  return std::make_tuple(username, password, cancelled);
}