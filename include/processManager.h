#pragma once
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <map>

/**
 * @class ProcessManager
 * @brief A class to manage background processes.
 *
 * This ProcessManager class provides functionality to add and manage background processes.
 */
class ProcessManager {
private:
    /**
     * @brief A map to store the background processes.
     *
     * The map associates process IDs (pids) with their corresponding command names.
     */
    std::map<pid_t, std::string> backgroundProcesses;

public:

    /**
     * @brief Adds a background process to the manager.
     *
     * This method adds a background process with its process ID (pid) and corresponding command name to the manager's process list.
     *
     * @param pid The process ID (pid) of the background process.
     * @param command The command associated with the background process.
     */
    void addProcess(pid_t pid, const std::string& command);

    /**
     * @brief Prints the currently running background processes.
     *
     * This method prints the process ID (pid) and command name of all currently running background processes.
     */
    void printProcesses();

    /**
     * @brief Cleans up finished background processes.
     *
     * This method uses waitpid to check on the status of background processes.
     * If a process has finished, it is removed from the manager's process list.
     */
    void cleanProcesses();
};
