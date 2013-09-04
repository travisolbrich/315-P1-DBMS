CC=g++
FLAGS=-std=c++11
BUILDDIR=build

all: project

project: $(BUILDDIR)/main.o $(BUILDDIR)/SqlTokenizer.o $(BUILDDIR)/Token.o $(BUILDDIR)/SqlParser.o $(BUILDDIR)/Engine.o
	$(CC) $(FLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/SqlTokenizer.o $(BUILDDIR)/Token.o $(BUILDDIR)/SqlParser.o $(BUILDDIR)/Engine.o  -o bin/project.out

$(BUILDDIR)/main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp -o $(BUILDDIR)/main.o

$(BUILDDIR)/SqlTokenizer.o: lib/SqlTokenizer/SqlTokenizer.cpp
	$(CC) $(FLAGS) -c lib/SqlTokenizer/SqlTokenizer.cpp -o $(BUILDDIR)/SqlTokenizer.o

$(BUILDDIR)/Token.o: lib/SqlTokenizer/Token.cpp
	$(CC) $(FLAGS) -c lib/SqlTokenizer/Token.cpp -o $(BUILDDIR)/Token.o

$(BUILDDIR)/SqlParser.o: lib/SqlParser/SqlParser.cpp
	$(CC) $(FLAGS) -c lib/SqlParser/SqlParser.cpp -o $(BUILDDIR)/SqlParser.o

$(BUILDDIR)/Engine.o: lib/DBMSEngine/Engine.cpp
	$(CC) $(FLAGS) -c lib/DBMSEngine/Engine.cpp -o $(BUILDDIR)/Engine.o

clean: 
	-rm -rf build/* 