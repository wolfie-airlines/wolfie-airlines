/**
 * @file tickets.h
 * @brief Ten plik zawiera deklaracje różnych funkcji obsługujących bilety.
 */

#ifndef AIRPORT_TICKETS_H
#define AIRPORT_TICKETS_H

#include "../flights/flight_connection.h"
#include "../user/user.h"

const int MAX_TICKETS = 4; ///< Maksymalna liczba biletów.
const int EMERGENCY_SEAT_ONE = 37; ///< Numer pierwszego miejsca awaryjnego.
const int EMERGENCY_SEAT_TWO = 45; ///< Numer drugiego miejsca awaryjnego.

/**
 * @brief Obsługuje wybór biletu przez użytkownika.
 * @param flight_connection Połączenie lotnicze.
 * @param user Użytkownik dokonujący wyboru.
 */
void HandleTicketChoice(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje zakup biletu.
 * @param choice Wybór użytkownika.
 * @param flight_connection Połączenie lotnicze.
 * @param user Użytkownik dokonujący zakupu.
 */
void HandleBuyTicket(int choice, FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje lot według jego ID.
 * @param flight_connection Połączenie lotnicze.
 * @param user Użytkownik.
 */
void HandleFlightById(FlightConnection &flight_connection, User &user);

/**
 * @brief Obsługuje lot według jego danych.
 * @param flight_connection Połączenie lotnicze.
 * @param user Użytkownik.
 */
void HandleFlightByData(FlightConnection &flight_connection, User &user);

/**
 * @brief Przetwarza zakup biletu.
 * @param flight_connection Połączenie lotnicze.
 * @param found_connection Znalezione połączenie lotnicze.
 * @param user Użytkownik dokonujący zakupu.
 */
void ProcessPurchase(
    FlightConnection &flight_connection,
    FlightConnection &found_connection,
    User &user);

#endif  // AIRPORT_TICKETS_H