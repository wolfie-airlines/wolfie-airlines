/**
 * @file profession_prints.h
 * @brief Ten plik zawiera deklaracje funkcji wyświetlania informacji o zawodzie i walidacji odpowiedzi.
 */

#ifndef AIRPORT_PROFESSION_PRINTS_H
#define AIRPORT_PROFESSION_PRINTS_H

#include <string>

#include "../../user.h"

/**
 * @brief Tworzy ekran zawodu.
 * @return Liczba całkowita reprezentująca status operacji.
 */
int CreateProfessionScreen();

/**
 * @brief Wyświetla informacje o zawodzie.
 * @return Ciąg znaków zawierający informacje o zawodzie.
 */
std::string DisplayProfessionInfo();

/**
 * @brief Obsługuje nieprawidłową odpowiedź.
 */
void InvalidAnswer();

/**
 * @brief Obsługuje prawidłową odpowiedź.
 * @param category Kategoria odpowiedzi.
 * @param user Użytkownik udzielający odpowiedzi.
 */
void ValidAnswer(const std::string &category, User &user);

#endif  // AIRPORT_PROFESSION_PRINTS_H