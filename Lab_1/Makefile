TARGET = lab1
CC = gcc
CFLAGS = -Wall -O3

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

.PHONY: default all clean

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f vgcore*