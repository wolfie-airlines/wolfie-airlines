#ifndef AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_
#define AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_

void DisplayAdminMenu();
void DisplayAddingFlightInfo();
std::string DisplayAdminMessageAndCaptureInput(const std::string &title_message, const std::string &text_message);
std::string DisplayAdminMessageAndCaptureLine(const std::string &title_message, const std::string &text_message);

#endif //AIRPORT_ADMIN_ADMIN_PRINTS_ADMIN_PRINTS_H_
