# set compiler
CC = g++

# set linker
LD = g++

# set compiler flags
CFLAGS = -Wall -pedantic -ggdb3 -Werror

# Sources for main program
SRCS = Reader.cpp Parser.cpp Runner.cpp MyShell.cpp shellProgram.cpp

# set target executable
TARGET = myShell

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Cleaning shell project
clean:
	$(RM) $(TARGET) *~
