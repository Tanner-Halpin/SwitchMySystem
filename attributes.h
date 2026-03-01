#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

class Attributes
{
private:
	string m_attribute, m_value;

public:
	void setAttribute(string& attribute);
	void setvalue(string& value);
	Attributes createAttribute(string& attribute, string& value);

	friend ostream& operator<<(ostream& out, Attributes& a);
};

#endif // !ATTRIBUTES_H