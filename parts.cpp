#include <iostream>
#include <vector>
#include <sstream>
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

	string name; // To be parsed into company, type, version and model

	cout << "\nEnter the full name of the " << partsName[count] << " component below: ";
	count++;
	
	getline(cin, name);
	stringstream ss(name);
	string word;
	
	string* attributesList[4]{ &d->company, &d->type, &d->version, &d->model };

	int i = 0;
	while (ss >> word)
	{
		*attributesList[i] = word;
		i++;

		if (i > 3)
			break;
	}
	i = 0;

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