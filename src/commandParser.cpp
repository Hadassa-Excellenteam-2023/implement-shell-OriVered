#include "commandParser.h"

std::vector<std::string> CommandParser::split(const std::string& input, char delimiter) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}