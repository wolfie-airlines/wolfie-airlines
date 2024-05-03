/**
 * @file admin_functions.h
 * @brief Ten plik zawiera deklaracje funkcji używanych w panelu administratora.
 */

#ifndef AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_
#define AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_

#include "../../user/user.h"

/**
 * @brief Obsługuje panel administratora.
 * @param admin Obiekt administratora.
 * @param user Obiekt użytkownika.
 */
void HandleAdminDashboard(Admin &admin, User &user);

/**
 * @brief Przetwarza dodanie lotu.
 * @return Ciąg znaków reprezentujący wynik operacji.
 */
std::string ProcessAddingFlight();

/**
 * @brief Przechwytuje dane wejściowe użytkownika z walidacją.
 * @param title Tytuł pola wejściowego.
 * @param message Wiadomość do wyświetlenia użytkownikowi.
 * @param validator Funkcja do walidacji danych wejściowych.
 * @return Przechwycone dane wejściowe.
 */
std::string CaptureInputWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

/**
 * @brief Przechwytuje linię danych wejściowych z walidacją.
 * @param title Tytuł pola wejściowego.
 * @param message Wiadomość do wyświetlenia użytkownikowi.
 * @param validator Funkcja do walidacji danych wejściowych.
 * @return Przechwycone dane wejściowe.
 */
std::string CaptureLineWithValidation(
    const std::string &title,
    const std::string &message,
    const std::function<bool(const std::string &)> &validator);

/**
 * @brief Przechwytuje wartość logiczną z walidacją.
 * @param title Tytuł pola wejściowego.
 * @param message Wiadomość do wyświetlenia użytkownikowi.
 * @return Opcjonalna wartość logiczna. Jeśli dane wejściowe są prawidłowe, wartością jest przechwycone dane wejściowe. Jeśli dane wejściowe są nieprawidłowe, wartością jest std::nullopt.
 */
std::optional<bool> CaptureBoolWithValidation(const std::string &title, const std::string &message);

#endif //AIRPORT_ADMIN_ADMIN_FUNCTIONS_ADMIN_FUNCTIONS_H_