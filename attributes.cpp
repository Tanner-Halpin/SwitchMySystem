#include <iostream>
#include <string>
#include "attributes.h"

using namespace std;

void Attributes::setAttribute(string& attribute) { m_attribute = attribute; }
void Attributes::setvalue(string& value) { m_value = value; }

Attributes Attributes::createAttribute(string& attribute, string& value)
{
	Attributes a;
	a.setAttribute(attribute), a.setvalue(value);

	return a;
}

ostream& operator<<(ostream& out, Attributes& a)
{
	out << a.m_attribute << ": " << a.m_value;
	return out;
}
