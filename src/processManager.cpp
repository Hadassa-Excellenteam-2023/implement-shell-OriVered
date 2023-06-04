#include "processManager.h"

void ProcessManager::printProcesses() {
    for (const auto& proc : backgroundProcesses) {
        std::cout << "PID: " << proc.first << ", Command: " << proc.second << "\n";
    }
}

void ProcessManager::addProcess(pid_t pid, const std::string& command) {
    backgroundProcesses[pid] = command;
}