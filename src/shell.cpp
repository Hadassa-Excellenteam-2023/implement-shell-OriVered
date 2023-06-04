#include "shell.h"

void Shell::runCommand(const std::string& command, bool inBackground) {
    std::vector<std::string> args = split(command, ' ');
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

        else {
            bool inBackground = command.back() == '&';
            if (inBackground) {
                command.pop_back(); // Remove the "&"
            }

            runCommand(command, inBackground);
        }
    }
}



std::vector<std::string> Shell::split(const std::string& input, char delimiter) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}