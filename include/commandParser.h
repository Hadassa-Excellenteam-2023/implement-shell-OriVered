#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>

/**
 * The CommandParser class is responsible for parsing and manipulating commands.
 */
class CommandParser {
public:
    /**
     * Splits a command into segments based on the specified delimiter.
     *
     * @param command    the command to split
     * @param delimiter  the delimiter used to split the command
     * @return a vector of segments obtained from splitting the command
     */
    static std::vector<std::string> splitCommand(const std::string& command, char delimiter);

    /**
     * Splits a command segment into two segments based on the specified delimiter.
     *
     * @param commandSegment  the command segment to split
     * @param delimiter       the delimiter used to split the command segment
     * @param segment1        the first segment obtained from splitting the command segment
     * @param segment2        the second segment obtained from splitting the command segment
     */
    static void splitCommandSegment(const std::string& commandSegment, char delimiter, std::string& segment1, std::string& segment2);

    /**
     * Trims leading and trailing whitespace from a string.
     *
     * @param str  the string to trim
     * @return the trimmed string
     */
    static std::string trim(const std::string& str);
};

#endif  // COMMANDPARSER_H
