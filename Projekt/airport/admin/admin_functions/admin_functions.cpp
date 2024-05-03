#include "admin_functions.h"
#include "../admin_prints/admin_prints.h"
#include "../../functions/info_prints/info_prints.h"
#include "../admin.h"

void HandleAdminDashboard(Admin &admin) {
  DisplayAdminMenu();
  std::string option;
  std::cin >> option;

  while (option != "quit") {
    if (option == "1") {
      admin.AddFlight();
    } else if (option == "2") {
      admin.AddVerificationQuestion();
    } else if (option == "3") {
      admin.ManageUsers();
    } else {
      PrintErrorMessage("Nieprawidłowy wybór.", "Spróbuj ponownie.");
    }
    DisplayAdminMenu();
    std::cin >> option;
  }
  // 2. Obsługa wyboru
  // 3. Implementacja funkcji
  // ^ Wszystko w pętli while
  // I. Funkcja dodająca loty
  // II. Funkcja dodająca pytania weryfikacyjne (dla danych zawodów)
  // III. Funkcja zarządzająca użytkownikami (usuwanie, blokowanie, zmiana konkretnej rzeczy w bazie danych: zawodu, zniżki, hasła, karty premium, itp.)
}