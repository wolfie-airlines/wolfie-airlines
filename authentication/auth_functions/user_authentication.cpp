#include "user_authentication.h"

#include "../../functions/info_prints/info_prints.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

std::tuple<std::string, std::string, std::string, bool> RegisterUser() {
    using namespace ftxui;
    std::string username;
    std::string email;
    std::string password;
    bool cancelled = false;

    Component input_username = Input(&username, "Your chosen username");

    Component input_email = Input(&email, "Your e-mail address");

    InputOption password_option;
    password_option.password = true;
    Component input_password = Input(&password, "Password", password_option);
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
                   hbox(text("Username : "), input_username->Render()),
                   hbox(text("Email             : "), input_email->Render()),
                   hbox(text("Password             : "), input_password->Render()),
                   separator(),
                   hbox(text("To confirm, click the Enter key") | bold | color(Color::YellowLight)),
                   hbox(text("If you want to cancel click the Escape key") | bold | color(Color::RedLight)),
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

    Component input_username = Input(&username, "Username");

    InputOption password_option;
    password_option.password = true;
    Component input_password = Input(&password, "Password", password_option);
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
                   hbox(text("Username : "), input_username->Render()),
                   hbox(text("Password   : "), input_password->Render()),
                   separator(),
                   hbox(text("To confirm, click ENTER") | bold | color(Color::YellowLight)),
                   hbox(text("If you want to cancel click the Escape key") | bold | color(Color::RedLight)),
               }) |
               border;
    });
    screen.Loop(renderer);

    return std::make_tuple(username, password, cancelled);
}

void HandleRegistration(Authentication &auth) {
    std::string username, email, password;
    bool cancelled;

    std::tie(username, email, password, cancelled) = RegisterUser();

    if (username.empty() && !cancelled) {
        PrintErrorMessage("No user name was provided.", "Try again.");
        return;
    }

    if (email.empty() && !cancelled) {
        PrintErrorMessage("No e-mail adress was provided.", "Try again.");
        return;
    }

    if (password.empty() && !cancelled) {
        PrintErrorMessage("No password was provided.", "Try again.");
        return;
    }

    if (cancelled) {
        PrintErrorMessage("Registration canceled.", "You can always try again.");
        return;
    }

    bool valid_register = auth.RegisterUser(username, email, password);

    if (valid_register) {
        PrintSuccessMessage("Registered successfully.", "Log in to continue.");
    } else {
        PrintErrorMessage("Registration failed.", "Try again.");
    }
}

bool HandleLogin(Authentication &auth, User &user) {
    std::string username, password;
    bool cancelled;
    std::tuple<std::string, std::string, bool> loginData = Login();
    std::tie(username, password, cancelled) = loginData;

    if (username.empty() && !cancelled) {
        PrintErrorMessage("No user name was provided.", "Try again.");
        return false;
    }

    if (password.empty() && !cancelled) {
        PrintErrorMessage("No password was provided.", "Try again.");
        return false;
    }

    if (cancelled) {
        PrintErrorMessage("Login canceled.", "You can always try again.");
        return false;
    }

    std::promise<bool> promise;

    auth.AuthenticateUser(username, password, std::move(promise), user);
    std::future<bool> future = promise.get_future();

    bool valid_login = future.get();

    if (valid_login) {
        return true;
    } else {
        PrintErrorMessage("Login failed.", "Try again with different data.");
        return false;
    }
}