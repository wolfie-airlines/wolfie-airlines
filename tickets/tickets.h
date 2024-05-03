/**
 * @file tickets.h
 * @brief This file contains the declaration of various ticket handling functions.
 */

#ifndef AIRPORT_TICKETS_H
#define AIRPORT_TICKETS_H

#include "../flights/flight_connection.h"
#include "../user/user.h"

const int MAX_TICKETS = 4; ///< The maximum number of tickets.
const int EMERGENCY_SEAT_ONE = 37; ///< The first emergency seat number.
const int EMERGENCY_SEAT_TWO = 45; ///< The second emergency seat number.

/**
 * @brief Handles the ticket choice of a user.
 * @param flight_connection The flight connection.
 * @param user The user making the choice.
 */
void HandleTicketChoice(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles the purchase of a ticket.
 * @param choice The choice of the user.
 * @param flight_connection The flight connection.
 * @param user The user making the purchase.
 */
void HandleBuyTicket(int choice, FlightConnection &flight_connection, User &user);

/**
 * @brief Handles the flight by its ID.
 * @param flight_connection The flight connection.
 * @param user The user.
 */
void HandleFlightById(FlightConnection &flight_connection, User &user);

/**
 * @brief Handles the flight by its data.
 * @param flight_connection The flight connection.
 * @param user The user.
 */
void HandleFlightByData(FlightConnection &flight_connection, User &user);

/**
 * @brief Processes the purchase of a ticket.
 * @param flight_connection The flight connection.
 * @param found_connection The found flight connection.
 * @param user The user making the purchase.
 */
void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user);

#endif  // AIRPORT_TICKETS_H