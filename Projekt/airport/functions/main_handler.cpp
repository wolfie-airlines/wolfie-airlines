#include <future>
#include <iostream>
#include <string>
#include <vector>

#include "../authentication/authentication.h"
#include "../authentication/auth_functions/user_authentication.h"
#include "../checkin/checkin_prints.h"
#include "../flights/flights_functions/flight_functions.h"
#include "../luggage/luggage_handler.h"
#include "../tickets/tickets.h"
#include "../tickets/tickets_prints/tickets_prints.h"
#include "../user/discounts/discounts.h"
#include "../user/premium_cards/premium_cards.h"
#include "../user/user_functions/user_prints/user_prints.h"
#include "../user/user_functions/user_settings/user_settings_handler.h"
#include "../user/user_functions/user_tickets/user_tickets_prints.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "info_prints/info_prints.h"

void HandleRegistration(Authentication &auth) {
  std::string username, email, password;
  bool cancelled;

  std::tie(username, email, password, cancelled) = RegisterUser();

  if (username.empty() && !cancelled) {
    PrintErrorMessage("Nie podano nazwy użytkownika.", "Spróbuj ponownie.");
    return;
  }

  if (email.empty() && !cancelled) {
    PrintErrorMessage("Nie podano adresu e-mail.", "Spróbuj ponownie.");
    return;
  }

  if (password.empty() && !cancelled) {
    PrintErrorMessage("Nie podano hasła.", "Spróbuj ponownie.");
    return;
  }

  if (cancelled) {
    PrintErrorMessage("Rejestracja anulowana.", "Zawsze możesz ponowić próbę.");
    return;
  }

  bool validRegister = auth.RegisterUser(username, email, password);

  if (validRegister) {
    PrintSuccessMessage("Zarejestrowano pomyślnie.", "Zaloguj się aby kontynuować.");
  } else {
    PrintErrorMessage("Rejestracja nie powiodła się.", "Spróbuj ponownie.");
  }
}

bool HandleLogin(Authentication &auth, User &user) {
  std::string username, password;
  bool cancelled;
  std::tuple<std::string, std::string, bool> loginData = Login();
  std::tie(username, password, cancelled) = loginData;

  if (username.empty() && !cancelled) {
    PrintErrorMessage("Nie podano nazwy użytkownika.", "Spróbuj ponownie.");
    return false;
  }

  if (password.empty() && !cancelled) {
    PrintErrorMessage("Nie podano hasła.", "Spróbuj ponownie.");
    return false;
  }

  if (cancelled) {
    PrintErrorMessage("Logowanie anulowane.", "Zawsze możesz ponowić próbę.");
    return false;
  }

  std::promise<bool> promise;

  auth.AuthenticateUser(username, password, std::move(promise), user);
  std::future<bool> future = promise.get_future();

  bool validLogin = future.get();

  if (validLogin) {
    return true;
  } else {
    PrintErrorMessage("Logowanie nie powiodło się.", "Spróbuj ponownie z innymi danymi.");
    return false;
  }
}

void HandleUserMenu(User &user) {
  auto
      userScreen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateUserMenu(user)));
  ftxui::Render(userScreen, *CreateUserMenu(user));
  std::cout << userScreen.ToString() << '\0' << std::endl;
}

void HandleMenu() {
  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(*CreateDefaultMenu()));
  ftxui::Render(screen, *CreateDefaultMenu());
  std::cout << screen.ToString() << '\0' << std::endl;
}

void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection) {
  while (true) {
    if (!is_logged_in) {
      HandleMenu();
      std::string choice;
      std::cin >> choice;

      if (choice == "1") {
        HandleRegistration(auth);
      } else if (choice == "2") {
        if (HandleLogin(auth, user)) {
          is_logged_in = true;
        }
      } else if (choice == "3") {
        HandleFlightOptions(flight_connection, user);
      } else if (choice == "4") {
        PrintErrorMessage("Musisz być zalogowany aby kupić bilet.", "Zaloguj się aby kontynuować.");
      } else if (choice == "5") {
        OpenWebsite();
      } else if (choice == "quit") {
        PrintSeeya();
        break;
      } else {
        PrintErrorMessage("Nieprawidłowy wybór.", "Spróbuj ponownie.");
      }
    } else {
      HandleUserMenu(user);
      std::string userChoice;
      std::cin >> userChoice;
      if (userChoice == "settings") {
        HandleSettingsOption(user);
      } else if (userChoice == "profil") {
        CreateProfileScreen(user);
      } else if (userChoice == "logout") {
        PrintLogout(user);
        is_logged_in = false;
      } else if (userChoice == "1") {
        HandleFlightOptions(flight_connection, user);
      } else if (userChoice == "2") {
        HandleTicketChoice(flight_connection, user);
      } else if (userChoice == "3") {
        if (user.discount_type_ == "ulga") {
          PrintErrorMessage("Nie możesz zakupić karty premium.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
        } else {
          HandlePremiumCard(user);
        }
      } else if (userChoice == "4") {
        if (user.discount_type_ == "premium") {
          PrintErrorMessage("Nie możesz starać się o ulgę.", "Posiadasz już zniżki z karty premium.");
        } else if (user.discount_type_ == "ulga") {
          PrintErrorMessage("Nie możesz starać się o ulgę.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
        } else {
          PrintDiscountCard(user);
        }
      } else if (userChoice == "5") {
        createTicketsScreen(user);
      } else if (userChoice == "6") {
        PrintCheckinScreen(user);
      } else if (userChoice == "7") {
        PrintWelcomeInCheckIn(user);
      } else if (userChoice == "8") {
        user.LoginAsAdmin();
      }
    }
  }
}
