CSCE 315 Project 1: DBMS
=============

To build the project, simply run `make`. The compiled code will be in `bin/`. The project is known to work well on the TAMU Sun server.

### Integration Submission (Sept 23)
Integration was already complete in the previous submission; please see the notes below for examples. 

Database files will be read and written to on the path that `bin/project.out` is run from.

### Parser Code Submission (Sept 16)

Please look at the [example input](ParserInput.md) and the [example output](PaserOutput.md). The input code was pasted directly into the terminal. The correct answer is given.

OPEN, CLOSE, and WRITE are not yet implemented.

### DBMS Engine Code Submission (Sept 9)

Please look at the [example output](output.md). The input is found in `src/main.cpp`. You can also compile the program as shown above and run `bin/project.out`.

We did not implement any comparison code in the select function. Our select function recieves a vector of integers that corresponds with the IDs of tuples in the relation. This vector of integers will be computed in the parser.

### Relevant Resources

* [Project Details](http://courses.cs.tamu.edu/choe/13fall/315/proj1.html)
* [Parser Example Inputs](http://students.cse.tamu.edu/aalap/CSCE315_s12/sample_inputs/parser_milestone_good_inputs.txt)
* [Design Document Guide](http://blog.slickedit.com/2007/05/how-to-write-an-effective-design-document/)


### Development Log

Please see the [Commit Log](https://github.com/travisolbrich/315-P1-DBMS/commits/master) for the most up-to-date and detailed development log. The below log will summarize major developments.

* 2013-09-23 Travis finished file IO.
* 2013-09-16 Travis finished the parser.
* 2013-09-15 Travis, Shane, John, and Adam met to finish the parser.
* 2013-09-09 Travis prepared the project for submission.
* 2013-09-08 Travis, Shane, John, and Adam met to finish the engine.
* 2013-09-07 Travis finished up union, difference, and product.
* 2013-09-04 Travis created the Relation data structure.
* 2013-09-03 Travis started work on the parser.
* 2013-09-03 Travis finished out the tokenizer.
* 2013-09-03 Shane added notes from the discussion about the DB engine 
* 2013-09-02 Travis worked on the tokenizer
* 2013-09-02 Travis, Shane, John, and Adam met to complete the [Design Document](doc/Design Document.md)
