#include "helpers.h"

#include <filesystem>
#include <iostream>
#include <thread>

#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha.h"

std::string ExtractFileName(const std::string &path) {
    std::filesystem::path filePath(path);
    std::string file_name = filePath.stem().string();
    return file_name;
}

void Countdown(int seconds, const std::string &type) {
    if (type == "music") {
        std::cout << "Focus! Playback will begin in: ";
    } else {
        std::cout << "Focus! Playback will begin in:  ";
    }
    for (int i = seconds; i >= 1; --i) {
        std::cout << i;
        std::cout.flush();  // Wymuszenie opróżnienia buforu, żeby nie zacięło odliczania
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\b";  // Cofanie kursora
    }
    std::cout << "1" << std::endl;
}

std::string HashString(const std::string &string_to_hash) {
    CryptoPP::SHA256 hash;
    std::string digest;
    CryptoPP::StringSource
        s(string_to_hash, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    return digest;
}

void SetCellColor(ftxui::Table &table, int col, int row, ftxui::Color color) {
    table.SelectCell(col, row).DecorateCells(ftxui::color(color));
}