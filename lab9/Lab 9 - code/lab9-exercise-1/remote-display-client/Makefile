all: remote-display-client


remote-display-client: remote-display-client.c ../balls.pb-c.c
	gcc remote-display-client.c ../balls.pb-c.c -o remote-display-client -g -lzmq -lncurses -lprotobuf-c