#ifndef ENVPARSER_H
#define ENVPARSER_H

#include <string>
#include <unordered_map>

class EnvParser {
   private:
    std::unordered_map<std::string, std::string> envMap;

   public:
    EnvParser();
    void parseEnvFile();
    [[nodiscard]] std::string getValue(const std::string& key) const;
};

#endif  // ENVPARSER_H
