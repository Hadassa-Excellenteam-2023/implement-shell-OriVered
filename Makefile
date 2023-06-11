# specify the compiler
CC = g++

# specify compiler flags
CFLAGS = -Wall -Iinclude

# specify the target file (the executable)
TARGET = main

# specify source files
SRCS = main.cpp src/shell.cpp src/processManager.cpp src/commandExecutor.cpp src/ioHandler.cpp src/commandParser.cpp

# specify object files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ $(TARGET)
