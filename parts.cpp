#include <iostream>
#include <vector>
#include "parts.h"

ostream& operator<<(ostream& out, Component& c)
{
	out << c.company << " " << c.type << " " << c.version << " " << c.model << "\n";
	for (auto& i : c.attributes)
	{
		out << "> " << i << "\n";
	}
	return out;
}

ifstream& operator>>(ifstream& in, Component& c)
{
	in >> c.company >> c.type >> c.version >> c.model;
	return in;
}

Component* Parts::CreateItem()
{
	vector<Component*> customPC;
	Component* d = new Component;

	cout << "\nComponent Entry Format: Company, Brand, Version, Model\nEnter the full name of the " << partsName[count] << " component below: ";
	count++;

	cin >> d->company >> d->type >> d->version >> d->model;
	customPC.push_back(d);
	componentList.push_back(d);

	cout << "\n" << endl;

	cout << "Part Added:\n\n";
	for (auto& i : customPC)
	{
		cout << " " << *i << "Address: " << i;
	}
	return d;
}