#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <string>
#include <vector>

/**
 * The CommandExecutor class is responsible for executing commands.
 */
class CommandExecutor {
public:
    /**
     * Executes a command.
     *
     * @param command  the command to execute
     */
    void executeCommand(const std::string& command);
};

#endif  // COMMAND_EXECUTOR_H
