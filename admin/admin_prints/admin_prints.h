/**
 * @file admin_prints.h
 * @brief Ten plik zawiera deklaracje funkcji używanych do wyświetlania informacji związanych z administratorem.
 */

#ifndef AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_
#define AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_

/**
 * @brief Wyświetla menu administratora.
 */
void DisplayAdminMenu();

/**
 * @brief Wyświetla informacje związane z dodawaniem lotu.
 */
void DisplayAddingFlightInfo();

/**
 * @brief Wyświetla wiadomość dla administratora i przechwytuje jego dane wejściowe.
 * @param title_message Tytuł wiadomości.
 * @param text_message Tekst wiadomości.
 * @return Dane wejściowe przechwycone od administratora.
 */
std::string DisplayAdminMessageAndCaptureInput(const std::string &title_message, const std::string &text_message);

/**
 * @brief Wyświetla wiadomość dla administratora i przechwytuje linię jego danych wejściowych.
 * @param title_message Tytuł wiadomości.
 * @param text_message Tekst wiadomości.
 * @return Linia danych wejściowych przechwycona od administratora.
 */
std::string DisplayAdminMessageAndCaptureLine(const std::string &title_message, const std::string &text_message);

/**
 * @brief Wyświetla menu zarządzania użytkownikami.
 */
void DisplayManageUsersMenu();

/**
 * @brief Wyświetla menu pomyślnej serializacji lotów.
 */
void DisplaySerializeMenu();

#endif //AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_