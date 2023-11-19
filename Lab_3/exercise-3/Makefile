CC = gcc
CFLAGS = -Wall -O3 -g -fPIC
LDLIBS = -lncurses
LDFLAGS =

# Name your targets
TARGET = human-control-client
TARGET2 = server
TARGET3 = machine-control-client

# Phony targets for all and clean
.PHONY: all clean

# Default target
all: $(TARGET) $(TARGET2) $(TARGET3)

# Compiling the source files into object files
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET2).o: $(TARGET2).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET3).o: $(TARGET3).c
	$(CC) $(CFLAGS) -c $< -o $@

# Linking the object files with ncurses library to make executable
$(TARGET): $(TARGET).o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(TARGET2): $(TARGET2).o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(TARGET3): $(TARGET3).o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

# Clean the build
clean:
	rm -f $(TARGET) $(TARGET2) $(TARGET3) *.o
