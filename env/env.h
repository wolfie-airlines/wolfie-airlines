/**
 * @file env.h
 * @brief Ten plik zawiera deklarację klasy EnvParser.
 */

#ifndef ENVPARSER_H
#define ENVPARSER_H

#include <string>
#include <unordered_map>

/**
 * @class EnvParser
 * @brief Ta klasa służy do analizy zmiennych środowiskowych.
 */
class EnvParser {
 private:
  std::unordered_map<std::string, std::string> _env_map_; ///< Mapa do przechowywania zmiennych środowiskowych.

 public:
  /**
   * @brief Konstruuje nowy obiekt EnvParser.
   */
  EnvParser();

  /**
   * @brief Analizuje plik środowiskowy.
   */
  void ParseEnvFile();

  /**
   * @brief Pobiera wartość określonej zmiennej środowiskowej.
   * @param key Klucz zmiennej środowiskowej.
   * @return Wartość zmiennej środowiskowej.
   */
  [[nodiscard]] std::string GetValue(const std::string &key) const;
};

#endif  // ENVPARSER_H