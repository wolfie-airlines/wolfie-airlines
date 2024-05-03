/**
 * @file profession_handler.h
 * @brief This file contains the declaration of various profession related question handling functions.
 */

#ifndef AIRPORT_PROFESSION_HANDLER_H
#define AIRPORT_PROFESSION_HANDLER_H

#include <string>

#include "../user.h"

/**
 * @brief Guesses the author of a music piece given a link.
 * @param music_link The link to the music piece.
 * @return True if the guess is correct, false otherwise.
 */
bool GuessMusicAuthor(const std::string &music_link);

/**
 * @brief Guesses the answer to a doctor related question.
 * @param user The user making the guess.
 * @return True if the guess is correct, false otherwise.
 */
bool GuessDoctorQuestion(User &user);

/**
 * @brief Guesses the answer to an informatics related question.
 * @param user The user making the guess.
 * @return True if the guess is correct, false otherwise.
 */
bool GuessInformaticQuestion(User &user);

/**
 * @brief Guesses the answer to a math related question.
 * @param user The user making the guess.
 * @return True if the guess is correct, false otherwise.
 */
bool GuessMathQuestion(User &user);

/**
 * @brief Displays information related to the police profession.
 * @return True if the operation is successful, false otherwise.
 */
bool DisplayPoliceProfession();

#endif  // AIRPORT_PROFESSION_HANDLER_H