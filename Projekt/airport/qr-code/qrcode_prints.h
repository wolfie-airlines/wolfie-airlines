#ifndef AIRPORT_QRCODE_PRINTS_H
#define AIRPORT_QRCODE_PRINTS_H

#include "qrcodegen.hpp"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


// Function prototypes
void createQR(std::string email, std::string username, std::string flightId, std::vector<int> seats);
void printQr(const QrCode &qr);


#endif //AIRPORT_QRCODE_PRINTS_H
