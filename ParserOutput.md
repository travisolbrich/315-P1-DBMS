# Output from the parser / integration test.

	travis@t420-ubuntu:~/school/csce315/project1$ bin/project.out
	sql> CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);

	INSERT INTO animals VALUES FROM ("Joe", "cat", 4);
	INSERT INTO animals VALUES FROM ("Spot", "dog", 10);
	INSERT INTO animals VALUES FROM ("Snoopy", "dog", 3);
	INSERT INTO animals VALUES FROM ("Tweety", "bird", 1);
	INSERT INTO animals VALUES FROM ("Joe", "bird", 2);

	dogs <- select (kind == "dog") animals;
	old_dogs <- select (years > 10) dogs;

	cats_or_dogs <- dogs + (select (kind == "cat") animals);

	CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);

	INSERT INTO species VALUES FROM RELATION project (kind) animals;

	a <- rename (aname, akind) (project (name, kind) animals);
	common_names <- project (name) (select (aname == name && akind != kind) (a * animals));
	answer <- common_names;

	SHOW answer;

	EXIT;sql> sql> sql> sql> sql> sql> sql> sql> sql> sql> sql> sql> sql> sql> ===== SHOW Relation: answer
	[KEY] VARCHAR name: Joe

	[KEY] VARCHAR name: Joe

	sql> EXIT;
