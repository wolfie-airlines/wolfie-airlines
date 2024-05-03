/**
 * @file qrcode_prints.h
 * @brief Ten plik zawiera deklaracje funkcji tworzenia i drukowania kodów QR.
 */

#ifndef AIRPORT_QRCODE_PRINTS_H
#define AIRPORT_QRCODE_PRINTS_H

#include "qrcodegen.hpp"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using std::uint8_t;

/**
 * @brief Tworzy kod QR na podstawie informacji o użytkowniku i locie.
 * @param email Adres email użytkownika.
 * @param username Nazwa użytkownika.
 * @param flight_id ID lotu.
 * @param seats Miejsca wybrane przez użytkownika.
 */
void CreateQr(const std::string &email,
              const std::string &username,
              const std::string &flight_id,
              std::vector<int> seats);

/**
 * @brief Drukuje kod QR.
 * @param qr Kod QR do wydrukowania.
 */
void PrintQr(const QrCode &qr);

#endif  // AIRPORT_QRCODE_PRINTS_H