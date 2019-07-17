# Makefile for the socket programming tutorial 
#
CXX=g++
CXXFLAGS=-Wl,--no-as-needed -std=c++11 -pthread
serverEXE = ./server/ServerSocket.o Socket.o ./server/server.o ./server/ServerSocket.h Socket.h SocketException.h 


clientEXE = ./client/ClientSocket.o Socket.o ./client/client.o ./server/ServerSocket.h Socket.h SocketException.h 

all : serverEXE clientEXE

serverEXE: $(serverEXE)
	g++ -std=c++11 -pthread -o serverEXE $(serverEXE)


clientEXE: $(clientEXE)
	g++ -std=c++11  -pthread -o clientEXE $(clientEXE)


Socket: Socket.cpp 
ServerSocket: ./server/ServerSocket.cpp 
ClientSocket: ./client/ClientSocket.cpp
serverEXE: ./server/server.cpp
clientEXE: ./client/client.cpp


clean:
	rm -f *.o serverEXE clientEXE ./server/*.o ./client/*.o
