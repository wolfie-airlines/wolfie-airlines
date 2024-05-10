#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <mmsystem.h>

#include <random>
#pragma comment(lib, "winmm.lib")

#include "../../functions/helpers.h"
#include "profession_handler.h"
#include "profession_prints/profession_prints.h"

void MusicProfession(User &user) {
    const std::string kSoundFiles[] = {
        "./sounds/acdc.wav",
        "./sounds/beethoven.wav",
        "./sounds/sinatra.wav",
        "./sounds/vacations.wav",
        "./sounds/vivaldi.wav",
        "./sounds/youngboy.wav"};

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, sizeof(kSoundFiles) / sizeof(kSoundFiles[0]) - 1);
    int random_index = dist(rng);
    std::string sound_file = kSoundFiles[random_index];

    Countdown(3, "music");
    PlaySound(TEXT(sound_file.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
    bool guessed = GuessMusicAuthor(ExtractFileName(sound_file));
    if (guessed) {
        ValidAnswer("musician", user);
    } else {
        InvalidAnswer();
    }
}

void DoctorProfession(User &user) {
    Countdown(3, "doctor");
    bool guess = GuessDoctorQuestion(user);
    if (guess) {
        ValidAnswer("doctor", user);
    } else {
        InvalidAnswer();
    }
}

void InformaticProfession(User &user) {
    Countdown(3, "informatic");
    bool guess = GuessInformaticQuestion(user);
    if (guess) {
        ValidAnswer("informatician", user);
    } else {
        InvalidAnswer();
    }
}

void MathProfession(User &user) {
    Countdown(3, "math");
    bool guess = GuessMathQuestion(user);
    if (guess) {
        ValidAnswer("mathematician", user);
        return;
    } else {
        InvalidAnswer();
        return;
    }
}

void PoliceProfession(User &user) {
    bool guess = DisplayPoliceProfession();
    if (guess) {
        ValidAnswer("policeman", user);
    } else {
        InvalidAnswer();
    }
}