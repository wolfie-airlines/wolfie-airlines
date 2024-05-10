#include "qrcode_prints.h"

#include <iostream>
#include <sstream>

void CreateQr(const std::string &email,
              const std::string &username,
              const std::string &flight_id,
              std::vector<int> seats) {
    std::string seats_string;
    for (size_t i = 0; i < seats.size(); ++i) {
        seats_string += std::to_string(seats[i]);
        if (i != seats.size() - 1) {
            seats_string += ",";
        }
    }

    std::string text =
        "https://wolfie-airlines-webpage.vercel.app/odprawy/" + username + "/" + email + "/" + flight_id + "/" + seats_string;

    const QrCode::Ecc kErrCorLvl = QrCode::Ecc::LOW;  // The less, the more opportunities for bits to be encoded

    std::vector<QrSegment> segs = QrSegment::makeSegments(text.c_str());
    const QrCode qr = QrCode::encodeSegments(segs, kErrCorLvl, 1, 40);
    PrintQr(qr);
}

void PrintQr(const QrCode &qr) {
    int border = 0;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            std::cout << (qr.getModule(x, y) ? "##" : "  ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
