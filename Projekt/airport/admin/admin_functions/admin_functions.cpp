#include "admin_functions.h"
#include "../admin.h"
#include "../admin_prints/admin_prints.h"
#include "../../functions/info_prints/info_prints.h"

std::string ProcessAddingFlight() {
  DisplayAddingFlightInfo();
  std::string input;
  std::cin >> input;
  return input;
}

void HandleAdminDashboard(Admin &admin, User &user) {
  DisplayAdminMenu();
  std::string option;
  std::cin >> option;

  while (option != "quit") {
    if (option == "1") {
      admin.AddFlight(user);
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

std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string&)>& validator) {
  std::string input = DisplayAdminMessageAndCaptureInput(title, message);
  while (!validator(input)) {
    PrintErrorMessage("Niepoprawne dane", message);
    if (input == "back") {
      PrintErrorMessage("Przerwano dodawanie lotu", "");
      return "";
    }
    input = DisplayAdminMessageAndCaptureInput(title, message);
  }
  return input;
}

bool ValidateFlightId(const std::string &flight_id) {
  return !flight_id.empty() && flight_id.length() == 5;
}

bool ValidateCity(const std::string &city) {
  return !city.empty();
}

bool ValidateDate(const std::string &date) {
  return !date.empty() && date.length() == 10 && date[2] == '.' && date[5] == '.';
}

bool ValidateTime(const std::string &time) {
  return !time.empty() && time.length() == 5 && time[2] == ':';
}

bool ValidatePrice(const std::string &price) {
  try {
    int price_int = std::stoi(price);
    return price_int >= 0;
  } catch (std::invalid_argument &e) {
    return false;
  }
}