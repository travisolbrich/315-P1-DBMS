#ifndef SQLTOKENIZER_INVALIDSYMBOLEXCEPTION_H_
#define SQLTOKENIZER_INVALIDSYMBOLEXCEPTION_H_

#include <iostream>
#include <exception>
using namespace std;

class InvalidSymbolException: public exception
{
  virtual const char* what() const throw()
  {
    return "You entered an incorrect symbol. Check your SQL code.";
  }
} InvalidSymbolException;

#endif