#include <iostream>
#include <string>

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
#include "info_prints/info_prints.h"
#include "main_prints/main_prints.h"
#include "../admin/admin_functions/admin_functions.h"
#include "../admin/admin.h"

void ProcessChoice(bool is_logged_in, Authentication &auth, User &user, FlightConnection &flight_connection) {
  while (true) {
    if (!is_logged_in) {
      DisplayMenu();
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
      DisplayUserMenu(user);
      std::string user_choice;
      std::cin >> user_choice;
      if (user_choice == "settings") {
        HandleSettingsOption(user);
      } else if (user_choice == "profil") {
        DisplayProfileScreen(user);
      } else if (user_choice == "logout") {
        PrintLogout(user);
        is_logged_in = false;
      } else if (user_choice == "1") {
        HandleFlightOptions(flight_connection, user);
      } else if (user_choice == "2") {
        HandleTicketChoice(flight_connection, user);
      } else if (user_choice == "3") {
        if (user.discount_type_ == "ulga") {
          PrintErrorMessage("Nie możesz zakupić karty premium.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
        } else {
          HandlePremiumCard(user);
        }
      } else if (user_choice == "4") {
        if (user.discount_type_ == "premium") {
          PrintErrorMessage("Nie możesz starać się o ulgę.", "Posiadasz już zniżki z karty premium.");
        } else if (user.discount_type_ == "ulga") {
          PrintErrorMessage("Nie możesz starać się o ulgę.", "Posiadasz już zniżki ze zweryfikowanej ulgi.");
        } else {
          PrintDiscountCard(user);
        }
      } else if (user_choice == "5") {
        CreateTicketsScreen(user);
      } else if (user_choice == "6") {
        PrintCheckinScreen(user);
      } else if (user_choice == "7") {
        PrintWelcomeInCheckIn(user);
      } else if (user_choice == "8") {
        Admin* admin = user.LoginAsAdmin();
        if(admin != nullptr){
          HandleAdminDashboard(*admin);
          delete admin; // Pamiętaj o usunięciu obiektu po użyciu
        }
      }
    }
  }
}
