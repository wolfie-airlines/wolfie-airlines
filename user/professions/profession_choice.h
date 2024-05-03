/**
 * @file profession_choice.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących wybór zawodu przez użytkownika.
 */

#ifndef AIRPORT_PROFESSION_CHOICE_H
#define AIRPORT_PROFESSION_CHOICE_H

#include "../user.h"

/**
 * @brief Obsługuje wybór zawodu muzycznego przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void MusicProfession(User &user);

/**
 * @brief Obsługuje wybór zawodu matematycznego przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void MathProfession(User &user);

/**
 * @brief Obsługuje wybór zawodu informatycznego przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void InformaticProfession(User &user);

/**
 * @brief Obsługuje wybór zawodu lekarskiego przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void DoctorProfession(User &user);

/**
 * @brief Obsługuje wybór zawodu policyjnego przez użytkownika.
 * @param user Użytkownik dokonujący wyboru.
 */
void PoliceProfession(User &user);

#endif  // AIRPORT_PROFESSION_CHOICE_H