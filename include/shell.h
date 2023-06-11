#ifndef SHELL_H
#define SHELL_H

#include <string>

/**
 * The Shell class represents a shell that can run commands.
 */
class Shell {
public:
    /**
     * Runs the shell.
     */
    void run();

private:
    /**
     * Runs a command in the shell.
     *
     * @param command       the command to run
     * @param inBackground  flag indicating whether the command should run in the background
     */
    void runCommand(const std::string& command, bool inBackground);

    /**
     * Processes a command in the shell.
     *
     * @param command  the command to process
     */
    void processCommand(const std::string& command);

    /**
     * Creates a child process to execute a command segment.
     *
     * @param commandSegment  the command segment to execute
     * @param fd_in           the input file descriptor
     * @param fd_out          the output file descriptor
     */
    void createChildProcess(const std::string& commandSegment, int fd_in, int fd_out);

    /**
     * Executes a command segment in the child process.
     *
     * @param commandSegment  the command segment to execute
     * @param fd_in           the input file descriptor
     * @param fd_out          the output file descriptor
     */
    void childProcess(const std::string& commandSegment, int fd_in, int fd_out);

    /**
     * Handles the parent process after creating a child process.
     *
     * @param pid           the process ID of the child process
     * @param inBackground  flag indicating whether the command is running in the background
     * @param command       the command being executed
     */
    void parentProcess(pid_t pid, bool inBackground, const std::string& command);

    /**
     * Duplicates a file descriptor.
     *
     * @param oldFd          the old file descriptor to duplicate
     * @param newFd          the new file descriptor to create
     * @param descriptorName the name of the file descriptor
     */
    void duplicateFileDescriptor(int oldFd, int newFd, const std::string& descriptorName);
};
#endif  // SHELL_H
