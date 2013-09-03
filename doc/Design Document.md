Design Document
===============

## Purpose of Project

For the Database Management System, the system is designed for use by a heavily enfranchised restaurant chain. The database will maintain a tracking of employee earnings throughout the entire company, keeping all of the varied branches in consideration. Such a database is necessary due to poor data management by other systems that the company has previously used. Employee earnings will be efficiently tracked based on multiple attributes including but not limited to: name, actualized earnings, city, and branch. These attributes will then be related so as to transgress to a more focused attribute pool. By using this system, a company will have unparalled precision when reviewing earning reports despite a heavy influx due to their large franchise numbers.

## High Level Entities

### DBMS 

![DBMS high-level organization](img/DBMS.png)



### DB App

![DB App high-level organization](img/DBApp.png)

## Low Level Design

### DBMS

#### Entity 1

#### Entity 2

### DB App

#### Entity 1

#### Entity 2

## Benefits, Assumptions, and Risks
A major foreseen benefit is simplicity. We will be implementing the DBMS by making use of relational algebra instead of more complicated and robust systems. By using relational algebra we also avoid the possibility of NULL values and duplicated tuples. This is a huge simplification when considering the table structure and overall code design. The assumption is that there are only six primitives which does yield a simpler code design, but queries will be more strict and verbose. This trade off is necessary in order to be able to produce the project in the desired timeline. As mentioned above we will be using six primitives. Listed below are the six and their functional description. (These descriptions are found in the project description under the Relational Algebra section)
Selection: select the tuples in a relation that satisfy a particular condition.
Projection: select a subset of the attributes in a relation.
Renaming: rename the attributes in a relation.
Set union: compute the union of two relations; the relations must be union-compatible.
Set difference: compute the set difference of two relations; the relations must be union-compatible.
Cross product: compute the Cartesian product of two relations.

An additional benefit is the implementation of the vector of vectors data structure to be used for generating tables (Relations). This will allow the DB engine to expand and traverse the relation space much more easily. The assumption is that we can store the attribute list in an array due to the fact that we will need to manipulate existing attributes but not add or remove them. A static storage structure such as an array will fit this design consideration most effectively. 

Another benefit is that the relations are stored in plain ascii text files. This is great due to portability issues and formatting. This is yet another layer of simplicity that will lend itself to be not only human readable (not binary or machine code), but also capable of being transported or run from various platforms.

For the DB App the assumption is the the interface will be implemented by way of CLI (command line interface). The benefit is that this will allow for increased flexibility across platforms and simplicity.

Being able to layer the DB App directly on top of the engine will be a benefit due to how tightly the interface can be implemented for queries.
