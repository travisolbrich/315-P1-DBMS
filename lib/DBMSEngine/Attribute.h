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

    Attribute(Type type, string value, bool primary) : type(type), value(value), primary(primary) {};
    Attribute(Type type, string value) : type(type), value(value), primary(false) {};
    Attribute() {};
    Type getType() { return type; }
    string getValue() { return value; }
    bool isPrimary() { return primary; }

    void setType(Type inType) { type = inType; }
    void setValue(string inValue) { value = inValue; }
    void setPrimary(bool inPrimary) { primary = inPrimary; }

  private:
    Type type;
    string value;
    bool primary;

};

#endif