#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <iostream>
#include <map>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * The ProcessManager class is responsible for managing background processes.
 */
class ProcessManager {
private:
    std::map<pid_t, std::string> backgroundProcesses;

    ProcessManager() = default;

public:
    /**
     * Gets the instance of the ProcessManager (singleton).
     *
     * @return the ProcessManager instance
     */
    static ProcessManager& getInstance() {
        static ProcessManager instance;
        return instance;
    }

    ProcessManager(const ProcessManager&) = delete;
    ProcessManager& operator=(const ProcessManager&) = delete;

    /**
     * Prints information about all the background processes.
     */
    void printProcesses();

    /**
     * Adds a background process to the process manager.
     *
     * @param pid      the process ID of the background process
     * @param command  the command associated with the background process
     */
    void addProcess(pid_t pid, const std::string& command);

    /**
     * Cleans up finished background processes.
     */
    void cleanProcesses();
};

#endif  // PROCESSMANAGER_H
