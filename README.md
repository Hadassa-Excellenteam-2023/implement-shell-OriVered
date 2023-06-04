﻿# implement-shell-OriVered-part-A

This project implements a basic shell in C++, capable of executing system commands.

## Features

- Run system commands
- Background job execution
- Command error handling

## Prerequisites

This program is designed to be run on a UNIX-based system. It requires the `g++` compiler and `make`.

## Compilation

This project comes with a Makefile. You can compile the project by simply running the `make` command in the project directory:

```bash	
make
```
The make command reads the Makefile to determine how to build the program.
The Makefile in this project compiles the source files and links the resulting object files to create the main executable.

## Execution
After compiling the project, you can run the shell program with the following command:
```bash	
./main
```

If you get a "permission denied" error when trying to run your executable,
you may need to add execute permissions to the file with the command 
```bash	
chmod +x main
```

The shell prompts for commands with a "> " prompt.
You can run any system command. Append '&' to the command to run it in the background.
Type myjobs to list background processes, and exit to quit the shell.
