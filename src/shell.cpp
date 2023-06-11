#include "shell.h"
#include "ioHandler.h"
#include "commandExecutor.h"
#include "commandParser.h"
#include "processManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Shell::run() {
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }
        else if (command == "myjobs") {
            ProcessManager::getInstance().printProcesses();
        }
        else {
            bool inBackground = !command.empty() && command.back() == '&';
            if (inBackground) {
                command.pop_back();
            }

            runCommand(command, inBackground);
        }
        ProcessManager::getInstance().cleanProcesses();
    }
}

void Shell::runCommand(const std::string& command, bool inBackground) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        processCommand(command);
        exit(EXIT_SUCCESS);
    }
    else {
        parentProcess(pid, inBackground, command);
    }
}

void Shell::processCommand(const std::string& command) {
    CommandParser parser;
    std::vector<std::string> pipes = parser.splitCommand(command, '|');
    int fd_in = STDIN_FILENO, fd[2];

    for (size_t commandIndex = 0; commandIndex < pipes.size(); ++commandIndex) {
        if (commandIndex != pipes.size() - 1) {
            if (pipe(fd) == -1) {
                perror("Failed to create pipe");
                exit(EXIT_FAILURE);
            }
        }

        createChildProcess(pipes[commandIndex], fd_in, commandIndex == pipes.size() - 1 ? STDOUT_FILENO : fd[1]);

        if (fd_in != STDIN_FILENO) {
            close(fd_in);
        }

        if (commandIndex != pipes.size() - 1) {
            close(fd[1]);
            fd_in = fd[0];
        }
    }
}
void Shell::createChildProcess(const std::string& commandSegment, int fd_in, int fd_out) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        childProcess(commandSegment, fd_in, fd_out);
    }
    else {
        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (fd_out != STDOUT_FILENO)
            close(fd_out);

        waitpid(pid, NULL, 0);
    }
}

void Shell::childProcess(const std::string& commandSegment, int fd_in, int fd_out) {
    CommandParser parser;

    std::string command = commandSegment;
    std::string inputSegment, outputSegment;

    if (command.find("<") != std::string::npos) {
        parser.splitCommandSegment(command, '<', command, inputSegment);
        inputSegment = parser.trim(inputSegment);
        if (!inputSegment.empty()) {
            IOHandler::getInstance().redirectInput(inputSegment);
        }
    }

    if (command.find(">") != std::string::npos) {
        parser.splitCommandSegment(command, '>', command, outputSegment);
        outputSegment = parser.trim(outputSegment);
        if (!outputSegment.empty()) {
            IOHandler::getInstance().redirectOutput(outputSegment);
        }
    }

    command = parser.trim(command);

    if (fd_in != STDIN_FILENO) {
        duplicateFileDescriptor(fd_in, STDIN_FILENO, "stdin");
    }
    if (fd_out != STDOUT_FILENO) {
        duplicateFileDescriptor(fd_out, STDOUT_FILENO, "stdout");
    }

    CommandExecutor executor;
    executor.executeCommand(command);

    if (!inputSegment.empty()) {
        IOHandler::getInstance().restoreInput();
    }

    if (!outputSegment.empty()) {
        IOHandler::getInstance().restoreOutput();
    }

    if (fd_in != STDIN_FILENO) {
        close(fd_in);
    }
    if (fd_out != STDOUT_FILENO) {
        close(fd_out);
    }
}

void Shell::parentProcess(pid_t pid, bool inBackground, const std::string& command) {
    if (!inBackground) {
        int status;
        if (waitpid(pid, &status, WUNTRACED) == -1) {
            perror("waitpid");
        }
    }
    else {
        ProcessManager::getInstance().addProcess(pid, command);
    }
}

void Shell::duplicateFileDescriptor(int oldFd, int newFd, const std::string& descriptorName) {
    if (dup2(oldFd, newFd) == -1) {
        perror(("Failed to duplicate file descriptor for " + descriptorName).c_str());
        exit(EXIT_FAILURE);
    }
    close(oldFd);
}

