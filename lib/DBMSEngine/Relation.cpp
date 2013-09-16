#include "Relation.h"

int Relation::getAttributeIDFromName(string name)
{
	for(int i=0; i < attributes.size(); i++)
	{
		if(attributes[i].getValue() == name)
		{
			return i;
		}
	}
	throw runtime_error("Attribute not found.");	
}