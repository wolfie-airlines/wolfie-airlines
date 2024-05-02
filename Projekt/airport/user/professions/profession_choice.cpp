#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <random>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "../../functions/helpers.h"
#include "profession_handler.h"
#include "profession_prints/profession_prints.h"

void MusicProfession(User &user) {
  const std::string soundFiles[] = {
      "./sounds/acdc.wav",
      "./sounds/beethoven.wav",
      "./sounds/sinatra.wav",
      "./sounds/vacations.wav",
      "./sounds/vivaldi.wav",
      "./sounds/youngboy.wav"};

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, sizeof(soundFiles) / sizeof(soundFiles[0]) - 1);
  int randomIndex = dist(rng);
  std::string randomSoundFile = soundFiles[randomIndex];

  Countdown(3, "music");
  PlaySound(TEXT(randomSoundFile.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
  bool guessed = GuessMusicAuthor(ExtractFileName(randomSoundFile));
  if (guessed) {
    ValidAnswer("muzyk", user);
  } else {
    InvalidAnswer();
  }
}

void DoctorProfession(User &user) {
  Countdown(3, "doctor");
  bool questionDisplayed = GuessDoctorQuestion(user);
  if (questionDisplayed) {
    ValidAnswer("lekarz", user);
  } else {
    InvalidAnswer();
  }
}

void InformaticProfession(User &user) {
  Countdown(3, "informatic");
  bool questionDisplayed = GuessInformaticQuestion(user);
  if (questionDisplayed) {
    ValidAnswer("informatyk", user);
  } else {
    InvalidAnswer();
  }
}

void MathProfession(User &user) {
  Countdown(3, "math");
  bool questionDisplayed = GuessMathQuestion(user);
  if (questionDisplayed) {
    ValidAnswer("matematyk", user);
    return;
  } else {
    InvalidAnswer();
    return;
  }
}

void PoliceProfession(User &user) {
  bool questionDisplayed = DisplayPoliceProfession(user);
  if (questionDisplayed) {
    ValidAnswer("policjant", user);
  } else {
    InvalidAnswer();
  }
}