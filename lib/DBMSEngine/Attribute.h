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

    Attribute(Type type, string value, bool primary, int size) : type(type), value(value), primary(primary), size(size) {};
    Attribute(Type type, string value, bool primary) : type(type), value(value), primary(primary) {};
    Attribute(Type type, string value) : type(type), value(value), primary(false) {};
    Attribute() {};
    
    Type getType() { return type; }
    string getValue() { return value; }
    int getSize() { return size; }
    bool isPrimary() { return primary; }
    string getTypeName() { return (type == VARCHAR) ? "VARCHAR" : "INTEGER"; }

    void setType(Type inType) { type = inType; }
    void setValue(string inValue) { value = inValue; }
    void setSize(int inSize) { size = inSize; }
    void setPrimary(bool inPrimary) { primary = inPrimary; }

  private:
    Type type;
    string value;
    int size;
    bool primary;

};

#endif