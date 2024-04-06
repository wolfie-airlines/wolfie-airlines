#ifndef AIRPORT_PROFESSION_PRINTS_H
#define AIRPORT_PROFESSION_PRINTS_H


#include <string>
#include "../../User.h"

int CreateProfessionScreen();
std::string displayProfessionInfo();
bool guessMusicAuthor(const std::string& musicLink);
void validAnswer(const std::string& category, User& user);
void invalidAnswer();

#endif //AIRPORT_PROFESSION_PRINTS_H