CC = gcc
CFLAGS = -Wall -O3 -g -fPIC
LDLIBS = -ldl
TARGET = client
TARGET2 = server
FUNCS = funcs.so

.PHONY: all clean

all: $(TARGET) $(FUNCS) $(TARGET2)

$(TARGET): client.o
	$(CC) client.o $(LDLIBS) -o $(TARGET)

$(TARGET2): server.o
	$(CC) server.o $(LDLIBS) -o $(TARGET2)

$(FUNCS): funcs.o
	$(CC) -shared funcs.o -o $(FUNCS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(FUNCS) $(TARGET2)