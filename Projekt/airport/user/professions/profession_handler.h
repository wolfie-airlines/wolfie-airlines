#ifndef AIRPORT_PROFESSION_HANDLER_H
#define AIRPORT_PROFESSION_HANDLER_H

#include <string>

#include "../user.h"

bool GuessMusicAuthor(const std::string &music_link);
bool GuessDoctorQuestion(User &user);
bool GuessInformaticQuestion(User &user);
bool GuessMathQuestion(User &user);
bool DisplayPoliceProfession(User &user);

#endif  // AIRPORT_PROFESSION_HANDLER_H
