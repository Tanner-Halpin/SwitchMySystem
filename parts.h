#ifndef PARTS_H
#define PARTS_H
#include "attributes.h"

struct Component
{
	string company="", type="", version="", model="";
	vector<Attributes> attributes;
};

ostream& operator<<(ostream& out, Component& c);
ifstream& operator>>(ifstream& in, Component& c);

class Parts : public Attributes
{
protected:
	vector<Component*> componentList;

public:
	int count = 0;
	vector<string> partsName = { "CPU", "Graphics Card", "Storage Device", "Memory Card", "Motherboard", "Power Supply" };
	Component* CreateItem();
};


#endif // !PARTS_H
