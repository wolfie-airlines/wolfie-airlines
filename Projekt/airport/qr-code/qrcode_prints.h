#ifndef AIRPORT_QRCODE_PRINTS_H
#define AIRPORT_QRCODE_PRINTS_H

#include "qrcodegen.hpp"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using std::uint8_t;

// Function prototypes
void createQR(const std::string& email, const std::string& username, const std::string& flightId, std::vector<int> seats);
void printQr(const QrCode& qr);

#endif  // AIRPORT_QRCODE_PRINTS_H
