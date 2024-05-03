/**
 * @file tickets_print_functions.h
 * @brief This file contains the declaration of various ticket printing functions.
 */

#ifndef TICKETS_PRINT_FUNCTIONS_H
#define TICKETS_PRINT_FUNCTIONS_H

#include <string>
#include <vector>

#include "../../flights/flight_connection.h"
#include "../../user/user.h"

/**
 * @brief Creates a ticket menu and returns the user's choice.
 * @return The user's choice as an integer.
 */
int CreateTicketMenu();

/**
 * @brief Checks if a choice is valid.
 * @param choice_title The title of the choice.
 * @param choice_text The text of the choice.
 * @return True if the choice is valid, false otherwise.
 */
bool ValidChoice(const std::string &choice_title, const std::string &choice_text);

/**
 * @brief Prints a ticket invoice.
 * @param user The user for whom the invoice is printed.
 * @param found_connection The flight connection for the ticket.
 * @param selected_seats The seats selected by the user.
 */
void PrintTicketInvoice(User &user, FlightConnection &found_connection, const std::vector<int> &selected_seats);

/**
 * @brief Opens a website.
 */
void OpenWebsite();

#endif  // TICKETS_PRINT_FUNCTIONS_H