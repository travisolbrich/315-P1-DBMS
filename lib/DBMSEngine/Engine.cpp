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
 
class Relations { 
