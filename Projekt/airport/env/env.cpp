#include "env.h"

#include <fstream>
#include <iostream>
#include <sstream>

// definicja konstruktora domyślnego -> inicjalizuje obiekt
EnvParser::EnvParser() = default;

void EnvParser::ParseEnvFile() {
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
      // Usunięcie białych znaków z klucza i wartości, gdyby ktoś zapomniał wyczyścić je w pliku .env
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(value.find_last_not_of(" \t") + 1);

      _env_map_[key] = value;
    }
  }

  file.close();
}

std::string EnvParser::GetValue(const std::string &key) const {
  auto it = _env_map_.find(key);
  if (it != _env_map_.end()) {
    return it->second;
  } else {
    return "Nie znaleziono klucza w pliku .env!";
  }
}