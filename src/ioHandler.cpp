#include "ioHandler.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

IOHandler& IOHandler::getInstance() {
    static IOHandler instance;
    return instance;
}

IOHandler::IOHandler() : originalInput(STDIN_FILENO), originalOutput(STDOUT_FILENO) {}

IOHandler::~IOHandler() {
    close(originalInput);
    close(originalOutput);
}

void IOHandler::redirectInput(const std::string& inputFile) {
    int fd0 = open(inputFile.c_str(), O_RDONLY);
    if (fd0 == -1) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    originalInput = dup(STDIN_FILENO);
    if (dup2(fd0, STDIN_FILENO) == -1) {
        perror("Failed to redirect stdin");
        exit(EXIT_FAILURE);
    }

    close(fd0);
}

void IOHandler::redirectOutput(const std::string& outputFile) {
    int fd1 = open(outputFile.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd1 == -1) {
        perror("Failed to create output file");
        exit(EXIT_FAILURE);
    }

    originalOutput = dup(STDOUT_FILENO);
    if (dup2(fd1, STDOUT_FILENO) == -1) {
        perror("Failed to redirect stdout");
        exit(EXIT_FAILURE);
    }

    // Only close the new file descriptor. Don't close STDOUT_FILENO here
    close(fd1);
}


void IOHandler::restoreInput() {
    if (dup2(originalInput, STDIN_FILENO) == -1) {
        perror("Failed to restore stdin");
        exit(EXIT_FAILURE);
    }
}

void IOHandler::restoreOutput() {
    if (dup2(originalOutput, STDOUT_FILENO) == -1) {
        perror("Failed to restore stdout");
        exit(EXIT_FAILURE);
    }
    // Close the original output after it has been restored
    close(originalOutput);
}
