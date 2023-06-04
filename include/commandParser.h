#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/**
 * @class CommandParser
 * @brief A class to parse command strings.
 *
 * This CommandParser class provides functionality to split a command string into separate arguments.
 */
class CommandParser {
public:

    /**
     * @brief Splits a string into separate arguments using a delimiter.
     *
     * This method takes a string and splits it into separate arguments using the specified delimiter.
     * The resulting arguments are stored in a vector and returned.
     *
     * @param input The input string to be split.
     * @param delimiter The character used as a delimiter to separate the arguments.
     * @return std::vector<std::string> A vector containing the separated arguments.
     */
    std::vector<std::string> split(const std::string& input, char delimiter);
};
