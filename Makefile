CC=g++
FLAGS=-std=c++11

all: main

main: 
	$(CC) $(FLAGS) src/main.cpp -o bin/main.o

clean: 
	-rm -f bin/main.o