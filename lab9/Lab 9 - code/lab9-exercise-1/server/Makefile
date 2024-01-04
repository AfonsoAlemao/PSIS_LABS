all: server


server: server.c ../balls.pb-c.c
	gcc server.c ../balls.pb-c.c  -o server -g -lzmq -lncurses -lprotobuf-c