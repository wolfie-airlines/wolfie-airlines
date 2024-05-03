/**
 * @file env.h
 * @brief This file contains the declaration of the EnvParser class.
 */

#ifndef ENVPARSER_H
#define ENVPARSER_H

#include <string>
#include <unordered_map>

/**
 * @class EnvParser
 * @brief This class is used for parsing environment variables.
 */
class EnvParser {
 private:
  std::unordered_map<std::string, std::string> _env_map_; ///< The map to store environment variables.

 public:
  /**
   * @brief Constructs a new EnvParser object.
   */
  EnvParser();

  /**
   * @brief Parses the environment file.
   */
  void ParseEnvFile();

  /**
   * @brief Gets the value of a specific environment variable.
   * @param key The key of the environment variable.
   * @return The value of the environment variable.
   */
  [[nodiscard]] std::string GetValue(const std::string &key) const;
};

#endif  // ENVPARSER_H