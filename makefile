.PHONY:all

all:client server
server:server.cc
	g++ server.cc -o server -std=c++17
client:client.cc
	g++ client.cc -o client -std=c++17

.PHONY:clean
clean:
	rm -r client server
