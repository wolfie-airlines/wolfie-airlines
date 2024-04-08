#include <iostream>
#include <filesystem>
#include <thread>
#include "helpers.h"

std::string extractFileName(const std::string& path) {
    std::filesystem::path filePath(path);
    std::string fileName = filePath.stem().string();
    return fileName;
}


void countdown(int seconds, std::string type) {
    if(type == "music") {
        std::cout << "Skup się! Odtwarzanie zacznie się za: ";
    } else {
        std:: cout << "Skup się! Problem wyświetli się za: ";
    }
    for (int i = seconds; i >= 1; --i) {
        std::cout << i;
        std::cout.flush(); // wymuszenie wyproznienia bufora zeby sie nie zacielo odliczanie
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\b"; // cofanie kursora
    }
    std::cout << "1" << std::endl;
}