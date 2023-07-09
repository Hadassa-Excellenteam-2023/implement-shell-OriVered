#include "commandParser.h"

#include <sstream>

std::vector<std::string> CommandParser::splitCommand(const std::string& command, char delimiter) {
    std::vector<std::string> result;
    std::string segment;
    std::istringstream stream(command);

    while (std::getline(stream, segment, delimiter)) {
        result.push_back(segment);
    }

    return result;
}

void CommandParser::splitCommandSegment(const std::string& commandSegment, char delimiter, std::string& segment1, std::string& segment2) {
    std::vector<std::string> segments = splitCommand(commandSegment, delimiter);
    segment1 = segments[0];
    if (segments.size() > 1) {
        segment2 = segments[1];
    }
}


std::string CommandParser::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos) {
        return "";
    }

    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}
