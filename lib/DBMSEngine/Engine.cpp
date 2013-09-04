/**
  * Start for DB Engine
  * Pseudocode previously used for now
  */

/**
  *class table
  *  -> array of attributes
  *  -> vector of tuple
  *     -> tuple is array of values
  */
  
/////////////////////////////////////////////////////////////////////////

/**
  *   table ||    people
  *   id    ||   f_name   ||   l_name
  *   -------------------------------------------------------------------------
  *   0     ||   travis   ||   olbrich
  *   1     ||   john     ||   leslie
  *   -------------------------------------------------------------------------
  */
  
/////////////////////////////////////////////////////////////////////////

/**
  *class table
  *   table name = people
  *   array attributes = {
  *       [int id]
  *       [str f_name]
  *       [str l_name] 
  *   }
  *   vector tuple = {
  *       array {0, "travis", "olbrich"}
  *       array {1, "john", "leslie"}
  *   }
  */

//////////////////////////////////////////////////////////////////////////

#include "Engine.h"

#include <vector>
#include <string>
#include <array>
#include <iostream>

using namespace std;
 
try
{
  bool exit_var = false;
  while(exit_var = false)
  {

    //print some message "welcome to DBMS" etc.
    //listen for input
    //throw exceptions for invalid input

  }

} 
catch (exception& e)
{
  //catch exceptions for invalid input
  //catch exceptions for various errors
  //do we need try blocks around the function statements in the header file?
  cerr << e.what() << "\n";

}
