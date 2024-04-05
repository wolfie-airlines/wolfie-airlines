#include "profession_choice.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <random>
#include "../../functions/helpers.h"
#pragma comment(lib, "winmm.lib")

void musicProfession() {
    const std::string soundFiles[] = {
            "./sounds/acdc.wav",
            "./sounds/beethoven.wav",
            "./sounds/greenday.wav",
            "./sounds/seven-nation-army.wav",
            "./sounds/vivaldi.wav",
            "./sounds/youbgboy.wav"
    };

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, sizeof(soundFiles) / sizeof(soundFiles[0]) - 1);
    int randomIndex = dist(rng);
    std::string randomSoundFile = soundFiles[randomIndex];

    countdown(3);
    std::cout << "Odtwarzam: " << extractFileName(randomSoundFile) << std::endl;
    PlaySound(TEXT(randomSoundFile.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
}