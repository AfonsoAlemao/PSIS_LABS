#sudo apt install protobuf-c-compiler
#sudo apt install libprotobuf-c-dev
all: balls.pb-c.c


balls.pb-c.c: balls.proto
	protoc-c --c_out=. balls.proto
