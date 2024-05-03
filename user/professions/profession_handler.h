/**
 * @file profession_handler.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących pytania związane z zawodem.
 */

#ifndef AIRPORT_PROFESSION_HANDLER_H
#define AIRPORT_PROFESSION_HANDLER_H

#include <string>

#include "../user.h"

/**
 * @brief Próbuje odgadnąć autora utworu muzycznego na podstawie linku.
 * @param music_link Link do utworu muzycznego.
 * @return Prawda, jeśli zgadnięcie jest poprawne, w przeciwnym razie fałsz.
 */
bool GuessMusicAuthor(const std::string &music_link);

/**
 * @brief Próbuje odgadnąć odpowiedź na pytanie związane z zawodem lekarza.
 * @param user Użytkownik, który próbuje odgadnąć.
 * @return Prawda, jeśli zgadnięcie jest poprawne, w przeciwnym razie fałsz.
 */
bool GuessDoctorQuestion(User &user);

/**
 * @brief Próbuje odgadnąć odpowiedź na pytanie związane z informatyką.
 * @param user Użytkownik, który próbuje odgadnąć.
 * @return Prawda, jeśli zgadnięcie jest poprawne, w przeciwnym razie fałsz.
 */
bool GuessInformaticQuestion(User &user);

/**
 * @brief Próbuje odgadnąć odpowiedź na pytanie związane z matematyką.
 * @param user Użytkownik, który próbuje odgadnąć.
 * @return Prawda, jeśli zgadnięcie jest poprawne, w przeciwnym razie fałsz.
 */
bool GuessMathQuestion(User &user);

/**
 * @brief Wyświetla informacje związane z zawodem policjanta.
 * @return Prawda, jeśli operacja jest udana, w przeciwnym razie fałsz.
 */
bool DisplayPoliceProfession();

#endif  // AIRPORT_PROFESSION_HANDLER_H