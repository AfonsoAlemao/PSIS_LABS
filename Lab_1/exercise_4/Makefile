CC = gcc
CFLAGS = -Wall -O3 -g -fPIC
LDLIBS = -ldl
TARGET = main
LIB1 = lib1.so
LIB2 = lib2.so

.PHONY: all clean

all: $(TARGET) $(LIB1) $(LIB2)

$(TARGET): main.o
	$(CC) main.o $(LDLIBS) -o $(TARGET)

$(LIB1): lib1.o
	$(CC) -shared lib1.o -o $(LIB1)

$(LIB2): lib2.o
	$(CC) -shared lib2.o -o $(LIB2)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(LIB1) $(LIB2)