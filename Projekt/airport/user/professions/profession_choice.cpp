#include <windows.h>
#include <mmsystem.h>
#include "profession_choice.h"
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <random>
#include "../../functions/helpers.h"
#include "prints/profession_prints.h"

void musicProfession() {
    const std::string soundFiles[] = {
            "./sounds/acdc.wav",
            "./sounds/beethoven.wav",
            "./sounds/greenday.wav",
            "./sounds/seven-nation-army.wav",
            "./sounds/vivaldi.wav",
            "./sounds/youngboy.wav"
    };

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, sizeof(soundFiles) / sizeof(soundFiles[0]) - 1);
    int randomIndex = dist(rng);
    std::string randomSoundFile = soundFiles[randomIndex];

    countdown(3);
    std::cout << "Odtwarzam: " << extractFileName(randomSoundFile) << std::endl;
    PlaySound(TEXT(randomSoundFile.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
    std::string answer = guessMusicAuthor(extractFileName(randomSoundFile));
    std::cout << answer << std::endl;

    std::string userAnswer;
    std::getline(std::cin, userAnswer);
    std::cout << "Twoja odpowiedź: " << userAnswer << std::endl;

}