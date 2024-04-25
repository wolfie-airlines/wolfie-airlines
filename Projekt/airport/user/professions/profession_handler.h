#ifndef AIRPORT_PROFESSION_HANDLER_H
#define AIRPORT_PROFESSION_HANDLER_H

#include <string>
#include "../User.h"

bool guessMusicAuthor(const std::string& musicLink);
bool guessDoctorQuestion(User& user);
bool guessInformaticQuestion(User& user);
bool guessMathQuestion(User& user);
bool displayPoliceProfession(User &user);


#endif //AIRPORT_PROFESSION_HANDLER_H
