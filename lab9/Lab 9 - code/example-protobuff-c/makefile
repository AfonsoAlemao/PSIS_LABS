all: zmq-client zmq-server

example.pb-c.h: example.proto
	protoc --c_out=. example.proto

zmq-client: client/zmq-client.c example.pb-c.h
	gcc client/zmq-client.c example.pb-c.c -g -o zmq-client -lzmq -lprotobuf-c

zmq-server: server/zmq-server.c example.pb-c.h
	gcc server/zmq-server.c example.pb-c.c -g -o zmq-server -lzmq -lprotobuf-c

clean: 
	rm zmq-server zmq-client example.pb-c.h