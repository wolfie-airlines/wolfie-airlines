#ifndef AIRPORT_PROFESSION_PRINTS_H
#define AIRPORT_PROFESSION_PRINTS_H

#include <string>

#include "../../user.h"

int CreateProfessionScreen();
std::string displayProfessionInfo();
void invalidAnswer();
void validAnswer(const std::string &category, User &user);

#endif  // AIRPORT_PROFESSION_PRINTS_H