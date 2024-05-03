#ifndef ENVPARSER_H
#define ENVPARSER_H

#include <string>
#include <unordered_map>

class EnvParser {
 private:
  std::unordered_map<std::string, std::string> _env_map_;

 public:
  EnvParser();
  void ParseEnvFile();
  [[nodiscard]] std::string GetValue(const std::string &key) const;
};

#endif  // ENVPARSER_H
