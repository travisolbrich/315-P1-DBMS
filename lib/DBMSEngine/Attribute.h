#ifndef DBMSENGINE_ATTRIBUTE_H
#define DBMSENGINE_ATTRIBUTE_H

using namespace std;

#include <iostream>
#include <string>
#include <vector>

class Attribute
{
	public:
    enum Type { VARCHAR, INTEGER };

    Attribute(Type type, string value) : type(type), value(value) {};
    Attribute() {};
    Type getType() { return type; }
    string getValue() { return value; }

    void setType(Type inType) { type = inType; }
    void setValue(string inValue) { value = inValue; }

  private:
    Type type;
    string value;

};

#endif