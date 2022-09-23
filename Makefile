CC = g++
CFLAGS = -c -Wall
INCLUDEPATH = -Iinclude

all: pmpml.exe
	./pmpml.exe

pmpml.exe: pmpml.cpp include/graph.h
	$(CC) $(INCLUDEPATH) pmpml.cpp -o pmpml.exe
