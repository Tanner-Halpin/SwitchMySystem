#include <iostream>
#include <vector>
#include "build.h"

bool operator==(const Component& p1, const Component& p2)
{
	return p1 == p2;
}

ostream& operator<<(ostream& out, PC& p)
{
	out << p.name << "'s PC Specifications: " << "\n" << "1.) " << *(p.CPU) << "\n" << "2.) " << *(p.GPU) << "\n" << "3.) " << *(p.SSD) << "\n" << "4.) " << *(p.RAM) << "\n" << "5.) " << *(p.Motherboard) << "\n" << "6.) " << *(p.PSU) << "\n";
	return out;
}

istream& operator>>(istream& in, PC& b)
{
	in >> b.name;
	return in;
}


bool Build::isBuildEqual(Component& p1, Component& p2)
{
	if (!(p1 == p2))
	{
		return false;
	}
	return true;
}

void Build::addAttribute(int choice)
{
	string attribute, value;

	cin.clear();
	cin.ignore(100, '\n');

	cout << "Enter attribute name: ";
	getline(cin, attribute);

	cout << "The value: ";
	getline(cin, value);

	componentList[choice]->attributes.push_back(createAttribute(attribute, value));

	loadAllParts();
	cout << "\n";
}

void Build::loadParts()
{
	string file, name;
	cout << "Enter the exact name of the file: ";
	cin >> file;

	ifstream out{ file };

	if (!out)
	{
		cerr << "Error reading file\n\n";
		startMenu();
	}
	else
	{
		Component* e = new Component;

		cout << "Enter your name, or username: ";
		cin >> name;
		PC* list = new PC;
		list->name = name;
		
		int count = 0;
		int temp = 0;
		if (componentList.size() > 1)
		{
			count = componentList.size();
			temp = count;
		}

		cout << "\n" << endl;

		while (out >> e->company >> e->type >> e->version >> e->model)
		{
			componentList.push_back(e);
			cout << *componentList[count];
			++count;
			e = new Component;
		}

		Component** compList[6] = { &list->CPU, &list->GPU, &list->SSD, &list->RAM, &list->Motherboard, &list->PSU };

		for (int i = 0; i < size(compList); i++)
		{
			*compList[i] = componentList[temp];
			++temp;
		}

		cout << "\n" << endl;
		buildRoster.push_back(*list);

		delete list;
		delete e;
		list = nullptr;
		e = nullptr;
	}
}

void Build::printUpload()
{
	cout << "\n\nCurrent PC Build Roster:\n\n";
	int count = 0;

	for (auto& i : buildRoster)
	{
		cout << i;
		count++;
	}
	cout << "\n\n";
}

void Build::newPC()
{
	while (true)
	{
		PC* build = new PC;

		cout << "\nEnter your name, or username: ";
		getline(cin, m_name);
		cout << m_name << "'s PC. \n";

		Component** compList[6] = { &build->CPU, &build->GPU, &build->SSD, &build->RAM, &build->Motherboard, &build->PSU };

		for (size_t i = 0; i < size(compList); i++)
		{
			*compList[i] = CreateItem();
		}

		build->name = m_name;

		buildRoster.push_back(*build);
		count = 0;

		printUpload();
		startMenu();

		delete build;
		build = nullptr;
	}
}

Build Build::startMenu()
{
	char option = 0;
	while (true && option != 'q')
	{
		cout << "Pick an option: \na: Upload a list of PC Specifications\nb: Create a new PC with Parts\nc: Load the PC Build Roster\nd: Modify the component details\nq: End the program\n\nEnter your choice: ";
		cin >> option;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (option)
		{
		case 'a':
			loadParts(); break;
		case 'b':
			newPC(); break;
		case 'c':
			printUpload(); break;
		case 'd':
			loadAllParts(); break;
		case 'q':
			exit(0); break;
		default:
			cout << "Invalid input. Please try again\n\n"; startMenu();
		}
	}
}

vector<Component*> Build::loadAllParts()
{
	if (componentList.size() == 0)
	{
		cout << "No components in the list\n\n";
		startMenu();
	}
	else
	{
		int j = 0;
		for (auto i = componentList.begin(); i != componentList.end(); ++i)
		{
			cout << "\n" << j + 1 << ".) " << *componentList[j] << "Address Identifier (ID): " << componentList[j] << "\n";
			j++;
		}
		cout << "\n";
		char choice;  int selection;

		cout << "Add Attributes to a Part (y/n) ";
		cin >> choice;

		switch (choice)
		{
		case 'y':
			cout << "Select part by number: ";
			cin >> selection;
			addAttribute(selection - 1);

		case 'n':
			return componentList;
		default:
			return componentList;
		}
	}
}