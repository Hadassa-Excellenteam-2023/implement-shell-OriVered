#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>

/**
 * The IOHandler class is responsible for managing input and output redirection.
 */
class IOHandler {
private:
    int originalInput;
    int originalOutput;

    IOHandler();

public:
    /**
     * Gets the instance of the IOHandler (singleton).
     *
     * @return the IOHandler instance
     */
    static IOHandler& getInstance();

    /**
     * Redirects the input to the specified file.
     *
     * @param inputFile  the name of the input file
     */
    void redirectInput(const std::string& inputFile);

    /**
     * Redirects the output to the specified file.
     *
     * @param outputFile  the name of the output file
     */
    void redirectOutput(const std::string& outputFile);

    /**
     * Restores the original input source.
     */
    void restoreInput();

    /**
     * Restores the original output destination.
     */
    void restoreOutput();
};

#endif  // IOHANDLER_H
