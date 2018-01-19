# set compiler
CC = g++

# set compiler flags
CFLAGS = -Wall -Werror -pedantic --std=gnu++11 -g

# set target executable
TARGET = dedup

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET) *~
