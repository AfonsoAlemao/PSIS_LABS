CC = gcc
CFLAGS = -Wall -O3 -g -fPIC
LDLIBS = -lncurses
LDFLAGS =

# Name your targets
TARGET = ncurses-example-1
TARGET2 = ncurses-example-2

# Phony targets for all and clean
.PHONY: all clean

# Default target
all: $(TARGET) $(TARGET2)

# Compiling the source files into object files
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET2).o: $(TARGET2).c
	$(CC) $(CFLAGS) -c $< -o $@

# Linking the object files with ncurses library to make executable
$(TARGET): $(TARGET).o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(TARGET2): $(TARGET2).o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

# Clean the build
clean:
	rm -f $(TARGET) $(TARGET2) *.o