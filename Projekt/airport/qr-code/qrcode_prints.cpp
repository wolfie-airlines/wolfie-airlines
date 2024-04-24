#include <iostream>
#include <sstream>
#include "qrcode_prints.h"


void createQR(const std::string& email, const std::string& username, const std::string& flightId, std::vector<int> seats) {
    std::string seatsString;
    for (size_t i = 0; i < seats.size(); ++i) {
        seatsString += std::to_string(seats[i]);
        if (i != seats.size() - 1) {
            seatsString += ",";
        }
    }

    std::string text = "https://wolfie-airlines-webpage.vercel.app/odprawy/" + username + "/" + email + "/" + flightId + "/" + seatsString;

    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW; // im mniej tym więcej możliwości bitów do zakodowania

    std::vector<QrSegment> segs = QrSegment::makeSegments(text.c_str());
    const QrCode qr = QrCode::encodeSegments(segs, errCorLvl, 1, 40);
    printQr(qr);
}

void printQr(const QrCode &qr) {
    int border = 0;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            std::cout << (qr.getModule(x, y) ? "##" : "  ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
