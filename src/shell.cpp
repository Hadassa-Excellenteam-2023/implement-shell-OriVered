#include "shell.h"

void Shell::runCommand(const std::string& command, bool inBackground) {
    std::vector<std::string> args = parser.split(command, ' ');
    std::vector<char*> cargs;
    for (const auto& arg : args) {
        cargs.push_back(const_cast<char*>(arg.c_str()));
    }
    cargs.push_back(NULL);

    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Failed to fork.\n";
        return;
    }
    else if (pid > 0) {
        // In parent process
        if (inBackground) {
            manager.addProcess(pid, args[0]);
        }
        else {
            waitpid(pid, NULL, 0);
        }
    }
    else {
        // In child process
        if (execvp(cargs[0], &cargs[0]) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}

void Shell::run() {
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }
        else if (command == "myjobs") {
            manager.printProcesses();
        }
        else {
            bool inBackground = command.back() == '&';
            if (inBackground) {
                command.pop_back(); // Remove the "&"
            }

            runCommand(command, inBackground);
        }
        manager.cleanProcesses();//remove finished prcoess from manager data
    }
}
