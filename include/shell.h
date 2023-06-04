#pragma once
#include <string>
#include <unistd.h>
#include "commandParser.h"
#include "processManager.h"

/**
 * @class Shell
 * @brief A class to simulate the behavior of a command line shell.
 *
 * This Shell class interfaces with CommandParser and ProcessManager to parse and execute commands.
 */
class Shell {
private:
    /**
     * @brief A CommandParser object used to parse the input commands.
     *
     * CommandParser will interpret a given string as a command, and format it for execution.
     */
    CommandParser parser;

    /**
     * @brief A ProcessManager object used to manage and execute processes.
     *
     * ProcessManager will manage the execution of processes as dictated by the given commands.
     */
    ProcessManager manager;

public:

    /**
     * @brief Executes a given command.
     *
     * This method will pass the command to the CommandParser to be parsed, and then to the ProcessManager to be executed.
     * If the 'inBackground' parameter is true, the ProcessManager will execute the command in the background.
     *
     * @param command A string containing the command to be executed.
     * @param inBackground A boolean indicating whether the command should be executed in the background.
     */
    void runCommand(const std::string& command, bool inBackground);

    /**
     * @brief The primary method for the Shell class.
     *
     * This method will start the shell, waiting for and executing commands until termination.
     */
    void run();
};
