#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>


class Shell {

public:
    void runCommand(const std::string& command, bool inBackground);
    void run();
    std::vector<std::string> split(const std::string& input, char delimiter);
};