CC=g++
FLAGS=-std=c++11 -g
BUILDDIR=build

all: project

project: $(BUILDDIR)/main.o $(BUILDDIR)/SqlTokenizer.o $(BUILDDIR)/Token.o $(BUILDDIR)/DBApp.o $(BUILDDIR)/Seeder.o $(BUILDDIR)/DBMS.o $(BUILDDIR)/SqlParser.o $(BUILDDIR)/Engine.o $(BUILDDIR)/ConditionParser.o $(BUILDDIR)/Relation.o
	$(CC) $(FLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/SqlTokenizer.o $(BUILDDIR)/Token.o $(BUILDDIR)/DBApp.o $(BUILDDIR)/Seeder.o $(BUILDDIR)/DBMS.o $(BUILDDIR)/SqlParser.o $(BUILDDIR)/Engine.o $(BUILDDIR)/ConditionParser.o $(BUILDDIR)/Relation.o -o bin/project.out

$(BUILDDIR)/main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp -o $(BUILDDIR)/main.o

$(BUILDDIR)/SqlTokenizer.o: lib/SqlTokenizer/SqlTokenizer.cpp
	$(CC) $(FLAGS) -c lib/SqlTokenizer/SqlTokenizer.cpp -o $(BUILDDIR)/SqlTokenizer.o

$(BUILDDIR)/Token.o: lib/SqlTokenizer/Token.cpp
	$(CC) $(FLAGS) -c lib/SqlTokenizer/Token.cpp -o $(BUILDDIR)/Token.o

$(BUILDDIR)/SqlParser.o: lib/SqlParser/SqlParser.cpp
	$(CC) $(FLAGS) -c lib/SqlParser/SqlParser.cpp -o $(BUILDDIR)/SqlParser.o

$(BUILDDIR)/ConditionParser.o: lib/SqlParser/ConditionParser.cpp
	$(CC) $(FLAGS) -c lib/SqlParser/ConditionParser.cpp -o $(BUILDDIR)/ConditionParser.o

$(BUILDDIR)/Engine.o: lib/DBMSEngine/Engine.cpp
	$(CC) $(FLAGS) -c lib/DBMSEngine/Engine.cpp -o $(BUILDDIR)/Engine.o

$(BUILDDIR)/Relation.o: lib/DBMSEngine/Relation.cpp
	$(CC) $(FLAGS) -c lib/DBMSEngine/Relation.cpp -o $(BUILDDIR)/Relation.o

$(BUILDDIR)/DBMS.o: lib/DBMS/DBMS.cpp
	$(CC) $(FLAGS) -c lib/DBMS/DBMS.cpp -o $(BUILDDIR)/DBMS.o

$(BUILDDIR)/Seeder.o: lib/DBSeeder/Seeder.cpp
	$(CC) $(FLAGS) -c lib/DBSeeder/Seeder.cpp -o $(BUILDDIR)/Seeder.o

$(BUILDDIR)/DBApp.o: lib/DBApplication/DBApp.cpp
	$(CC) $(FLAGS) -c lib/DBApplication/DBApp.cpp -o $(BUILDDIR)/DBApp.o

clean: 
	-rm -rf build/* 