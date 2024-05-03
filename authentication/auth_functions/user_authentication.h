/**
 * @file user_authentication.h
 * @brief Ten plik zawiera deklaracje funkcji używanych do uwierzytelniania użytkownika.
 */

#ifndef AIRPORT_AUTHPRINTHANDLER_H
#define AIRPORT_AUTHPRINTHANDLER_H

#include <string>
#include <tuple>
#include "../../user/user.h"
#include "../authentication.h"

/**
 * @brief Rejestruje nowego użytkownika.
 * @return Krotka zawierająca nazwę użytkownika, hasło, email i wartość logiczną wskazującą, czy rejestracja była udana.
 */
std::tuple<std::string, std::string, std::string, bool> RegisterUser();

/**
 * @brief Loguje użytkownika.
 * @return Krotka zawierająca nazwę użytkownika, hasło i wartość logiczną wskazującą, czy logowanie było udane.
 */
std::tuple<std::string, std::string, bool> Login();

/**
 * @brief Obsługuje proces rejestracji.
 * @param auth Obiekt Authentication.
 */
void HandleRegistration(Authentication &auth);

/**
 * @brief Obsługuje proces logowania.
 * @param auth Obiekt Authentication.
 * @param user Obiekt User.
 * @return Wartość logiczna wskazująca, czy logowanie było udane.
 */
bool HandleLogin(Authentication &auth, User &user);

#endif  // AIRPORT_AUTHPRINTHANDLER_H