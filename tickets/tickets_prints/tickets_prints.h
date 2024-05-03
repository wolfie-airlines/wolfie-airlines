/**
 * @file tickets_print_functions.h
 * @brief Ten plik zawiera deklaracje różnych funkcji drukowania biletów.
 */

#ifndef TICKETS_PRINT_FUNCTIONS_H
#define TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../flights/flight_connection.h"
#include "../../user/user.h"

/**
 * @brief Tworzy menu biletów i zwraca wybór użytkownika.
 * @return Wybór użytkownika jako liczba całkowita.
 */
int CreateTicketMenu();

/**
 * @brief Sprawdza, czy wybór jest prawidłowy.
 * @param choice_title Tytuł wyboru.
 * @param choice_text Tekst wyboru.
 * @return Prawda, jeśli wybór jest prawidłowy, w przeciwnym razie fałsz.
 */
bool ValidChoice(const std::string &choice_title, const std::string &choice_text);

/**
 * @brief Drukuje fakturę za bilet.
 * @param user Użytkownik, dla którego drukowana jest faktura.
 * @param found_connection Połączenie lotnicze dla biletu.
 * @param selected_seats Miejsca wybrane przez użytkownika.
 */
void PrintTicketInvoice(User &user, FlightConnection &found_connection, const std::vector<int> &selected_seats);

/**
 * @brief Otwiera stronę internetową.
 */
void OpenWebsite();

#endif  // TICKETS_PRINT_FUNCTIONS_H