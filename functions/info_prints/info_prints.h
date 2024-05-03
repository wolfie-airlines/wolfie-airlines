/**
 * @file functions.h
 * @brief Ten plik zawiera deklaracje różnych funkcji drukujących.
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "../../user/user.h"

/**
 * @brief Drukuje komunikat o sukcesie.
 * @param title_message Tytuł komunikatu.
 * @param optional_message Opcjonalny komunikat do wyświetlenia.
 */
void PrintSuccessMessage(const std::string &title_message, const std::string &optional_message);

/**
 * @brief Drukuje komunikat o błędzie.
 * @param title_message Tytuł komunikatu.
 * @param optional_message Opcjonalny komunikat do wyświetlenia.
 */
void PrintErrorMessage(const std::string &title_message, const std::string &optional_message);

/**
 * @brief Drukuje komunikat o wylogowaniu użytkownika.
 * @param user Użytkownik, który się wylogowuje.
 */
void PrintLogout(User &user);

/**
 * @brief Drukuje komunikat na pożegnanie.
 */
void PrintSeeya();

#endif  // FUNCTIONS_H