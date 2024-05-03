/**
 * @file profession_choice.h
 * @brief This file contains the declaration of various profession choice functions.
 */

#ifndef AIRPORT_PROFESSION_CHOICE_H
#define AIRPORT_PROFESSION_CHOICE_H

#include "../user.h"

/**
 * @brief Handles the music profession choice of a user.
 * @param user The user making the choice.
 */
void MusicProfession(User &user);

/**
 * @brief Handles the math profession choice of a user.
 * @param user The user making the choice.
 */
void MathProfession(User &user);

/**
 * @brief Handles the informatics profession choice of a user.
 * @param user The user making the choice.
 */
void InformaticProfession(User &user);

/**
 * @brief Handles the doctor profession choice of a user.
 * @param user The user making the choice.
 */
void DoctorProfession(User &user);

/**
 * @brief Handles the police profession choice of a user.
 * @param user The user making the choice.
 */
void PoliceProfession(User &user);

#endif  // AIRPORT_PROFESSION_CHOICE_H