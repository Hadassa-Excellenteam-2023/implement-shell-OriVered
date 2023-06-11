#include "commandExecutor.h"
#include "commandParser.h"

#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <errno.h>

void CommandExecutor::executeCommand(const std::string& command) {
    // Split the command into words
    std::vector<std::string> words = CommandParser::splitCommand(command, ' ');

    // Convert std::vector<std::string> to std::vector<char*>
    std::vector<char*> args;
    for (const std::string& word : words) {
        args.push_back(const_cast<char*>(word.c_str()));
    }
    // Add a null pointer at the end, because execvp expects a null-terminated array
    args.push_back(nullptr);

    // Now, execute the command
    execvp(args[0], args.data());

    // If execvp fails, display an error message
    perror(("Failed to execute command: " + command).c_str());
    exit(EXIT_FAILURE);
}
