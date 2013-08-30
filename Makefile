CC=g++
FLAGS=-std=c++11
BUILDDIR=build

all: project

project: main.o SqlTokenizer.o
	$(CC) $(FLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/SqlTokenizer.o -o bin/project.out

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp -o $(BUILDDIR)/main.o

SqlTokenizer.o: lib/SqlTokenizer/SqlTokenizer.cpp
	$(CC) $(FLAGS) -c lib/SqlTokenizer/SqlTokenizer.cpp -o $(BUILDDIR)/SqlTokenizer.o

clean: 
	-rm -rf build/* 