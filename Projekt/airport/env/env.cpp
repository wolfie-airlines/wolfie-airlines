#include "env.h"

#include <fstream>
#include <iostream>
#include <sstream>

// definicja konstruktora domyślnego -> inicjalizuje obiekt
EnvParser::EnvParser() = default;

void EnvParser::parseEnvFile() {
  const std::string &filename = ".env";
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku .env!" << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key, value;

    if (std::getline(iss, key, '=') && std::getline(iss, value)) {
      // usuniecie bialych znakow z konca jakby ktos zapomnial ich usunac
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(value.find_last_not_of(" \t") + 1);

      envMap[key] = value;
    }
  }

  file.close();
}

std::string EnvParser::getValue(const std::string &key) const {
  auto it = envMap.find(key);
  if (it != envMap.end()) {
    return it->second;
  } else {
    return "Nie znaleziono klucza w pliku .env!";
  }
}