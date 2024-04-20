#include <iostream>
#include <sstream>
#include "qrcode_prints.h"


void createQR(std::string email, std::string username, std::string flightId, std::vector<int> seats) {
    const char *text = "https://www.szymon-wilczek.pl";
    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // poziom korekcji pixeli

    std::vector<QrSegment> segs = QrSegment::makeSegments(text);
    const QrCode qr = QrCode::encodeSegments(segs, errCorLvl, 1, 2);
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

//std::string printQr(const QrCode &qr) {
//    int border = 0;
//    std::ostringstream qrString;
//    for (int y = -border; y < qr.getSize() + border; y++) {
//        for (int x = -border; x < qr.getSize() + border; x++) {
//            qrString << (qr.getModule(x, y) ? "##" : "  ");
//        }
//        qrString << "\n";
//    }
//    qrString << "\n";
//    return qrString.str();
//}
