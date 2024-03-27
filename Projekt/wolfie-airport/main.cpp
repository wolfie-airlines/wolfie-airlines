#include <iostream>
#include <chrono>
#include <thread>

void typeWriterEffect(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50 + rand() % 50)); // Losowe opóźnienie 50-100 ms
    }
}

int main() {
    std::string welcomeMsg = "Witamy na lotnisku Wolfie Airport!";
    std::string guideMsg = "Ponizej znajduje sie menu. Wybierz jedna z opcji:";
    typeWriterEffect(welcomeMsg);
    std::cout << std::endl;
    typeWriterEffect(guideMsg);
    std::cout << std::endl;

    return 0;
}
