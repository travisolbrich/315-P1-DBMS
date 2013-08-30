CC=g++

all: main

main: 
	$(CC) src/main.cpp -o bin/main.o

clean: 
	-rm -f bin/main.o