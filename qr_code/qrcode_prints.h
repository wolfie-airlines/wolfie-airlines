/**
 * @file qrcode_prints.h
 * @brief This file contains the declaration of QR code creation and printing functions.
 */

#ifndef AIRPORT_QRCODE_PRINTS_H
#define AIRPORT_QRCODE_PRINTS_H

#include "qrcodegen.hpp"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using std::uint8_t;

/**
 * @brief Creates a QR code based on user and flight information.
 * @param email The email of the user.
 * @param username The username of the user.
 * @param flight_id The ID of the flight.
 * @param seats The seats selected by the user.
 */
void CreateQr(const std::string &email,
              const std::string &username,
              const std::string &flight_id,
              std::vector<int> seats);

/**
 * @brief Prints a QR code.
 * @param qr The QR code to print.
 */
void PrintQr(const QrCode &qr);

#endif  // AIRPORT_QRCODE_PRINTS_H