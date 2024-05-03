#ifndef AIRPORT_QRCODE_PRINTS_H
#define AIRPORT_QRCODE_PRINTS_H

#include "qrcodegen.hpp"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using std::uint8_t;

void CreateQr(const std::string &email,
              const std::string &username,
              const std::string &flight_id,
              std::vector<int> seats);
void PrintQr(const QrCode &qr);

#endif  // AIRPORT_QRCODE_PRINTS_H
