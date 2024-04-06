#include "prints/profession_prints.h"
#include "../../functions/helpers.h"
#include "profession_handler.h"
#include <iostream>
#include <random>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

void musicProfession(User& user) {
    const std::string soundFiles[] = {
            "./sounds/acdc.wav",
            "./sounds/beethoven.wav",
            "./sounds/sinatra.wav",
            "./sounds/vacations.wav",
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
    bool guessed = guessMusicAuthor(extractFileName(randomSoundFile));
    if(guessed) {
        validAnswer("muzyk", user);
    } else {
        invalidAnswer();
    }

}

void doctorProfession(User& user) {
    countdown(3);
    bool questionDisplayed = guessDoctorQuestion(user);
    if(questionDisplayed) {
        validAnswer("lekarz", user);
    } else {
        invalidAnswer();
    }
}