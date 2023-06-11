#include "processManager.h"

void ProcessManager::printProcesses() {
    for (const auto& proc : backgroundProcesses) {
        std::cout << "PID: " << proc.first << ", Command: " << proc.second << "\n";
    }
}

void ProcessManager::addProcess(pid_t pid, const std::string& command) {
    backgroundProcesses[pid] = command;
}


void ProcessManager::cleanProcesses() {
    for (auto it = backgroundProcesses.begin(); it != backgroundProcesses.end(); /* no increment */) {
        int status;
        pid_t result = waitpid(it->first, &status, WNOHANG);
        if (result == 0) {
            // child still running
            ++it;
        }
        else if (result == -1) {
            // error occurred
            ++it;
        }
        else {
            // child finished, so remove it from our map
            it = backgroundProcesses.erase(it);
        }
    }
}
