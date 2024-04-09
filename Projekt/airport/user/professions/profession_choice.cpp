#include "profession_prints/profession_prints.h"
#include "../../functions/helpers.h"
#include "profession_handler.h"
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

    countdown(3, "music");
    PlaySound(TEXT(randomSoundFile.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
    bool guessed = guessMusicAuthor(extractFileName(randomSoundFile));
    if(guessed) {
        validAnswer("muzyk", user);
    } else {
        invalidAnswer();
    }

}

void doctorProfession(User& user) {
    countdown(3, "doctor");
    bool questionDisplayed = guessDoctorQuestion(user);
    if(questionDisplayed) {
        validAnswer("lekarz", user);
    } else {
        invalidAnswer();
    }
}

void informaticProfession(User& user) {
    countdown(3, "informatic");
    bool questionDisplayed = guessInformaticQuestion(user);
    if(questionDisplayed) {
        validAnswer("informatyk", user);
    } else {
        invalidAnswer();
    }
}

void mathProfession(User& user) {
    countdown(3, "math");
    bool questionDisplayed = guessMathQuestion(user);
    if(questionDisplayed) {
        validAnswer("matematyk", user);
        return;
    } else {
        invalidAnswer();
        return;
    }
}