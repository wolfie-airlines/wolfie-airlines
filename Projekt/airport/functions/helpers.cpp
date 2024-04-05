#include "helpers.h"
#include <iostream>
#include <filesystem>
#include <synchapi.h>

std::string extractFileName(const std::string& path) {
    std::filesystem::path filePath(path);
    std::string fileName = filePath.stem().string();
    return fileName;
}

void countdown(int seconds) {
    std::cout << "Skup się! Odtwarzanie zacznie się za: ";
    for (int i = seconds; i >= 1; --i) {
        std::cout << i;
        std::cout.flush(); // wymuszenie wyproznienia bufora zeby sie nie zacielo odliczanie
        Sleep(1000);
        std::cout << "\b"; // cofanie kursora
    }
    std::cout << "1" << std::endl;
}