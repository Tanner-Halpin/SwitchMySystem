#include <iostream> 
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class Attributes
{
private:
	string m_attribute, m_value;
	unordered_map<string, string> map;

public:
	void setAttribute(string& attribute) { m_attribute = attribute; }
	void setvalue(string& value) { m_value = value; }

	Attributes createAttribute(string& attribute, string& value)
	{
		Attributes a;
		a.setAttribute(attribute), a.setvalue(value);

		map[m_attribute] = m_value;

		return a;
	}

	friend ostream& operator<<(ostream& out, Attributes& a)
	{
		out << a.m_attribute << ": " << a.m_value;
		return out;
	}
};

struct Component
{
	string company, type, version, model;
	vector<Attributes> attributes;
};


ostream& operator<<(ostream& out, Component& c)
{
	out << c.company << " " << c.type << " " << c.version << " " << c.model << "\n";
	for (auto& i : c.attributes)
	{
		out << "> " << i << "\n";
	}
	return out;
}

struct PC
{
	string name;
	Component* CPU = NULL; Component* GPU = NULL; Component* SSD = NULL; Component* RAM = NULL; Component* Motherboard = NULL; Component* PSU = NULL;
};


class Parts : public Attributes
{
protected:
	vector<Component*> componentList;

public:
	int count = 0;
	vector<string> partsName = { "CPU", "Graphics Card", "Storage Device", "Memory Card", "Motherboard", "Power Supply" };

	Component* CreateItem()
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
};

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

ifstream& operator>>(ifstream& in, Component& c)
{
	in >> c.company >> c.type >> c.version >> c.model;
	return in;
}

bool operator==(const Component& p1, const Component& p2)
{
	return p1 == p2;
}

class Build : public Parts
{
protected:
	string m_name;
	vector<PC> buildRoster;

public:

	bool isBuildEqual(Component& p1, Component& p2)
	{
		if (!(p1 == p2))
		{
			return false;
		}
		return true;
	}

	void addAttribute(int choice)
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

	void loadParts()
	{
		string file, name;
		cout << "Enter the exact name of the file: ";
		cin >> file;

		ifstream out{ file };

		if (!out)
		{
			cerr << "Error reading file\n";
			loadParts();
		}
		else
		{
			Component* d = new Component;

			cout << "Name your Computer: ";
			cin >> name;
			PC* list = new PC;
			list->name = name;

			int count = 0;
			cout << "\n" << endl;

			while (out >> d->company >> d->type >> d->version >> d->model)
			{
				componentList.push_back(d);
				cout << *componentList[count];
				++count;
				d = new Component;
			}

			Component** compList[6] = { &list->CPU, &list->GPU, &list->SSD, &list->RAM, &list->Motherboard, &list->PSU };

			for (int i = 0; i < size(compList); i++)
			{
				*compList[i] = componentList[i];
			}

			cout << "\n" << endl;
			buildRoster.push_back(*list);

			delete list;
			delete d;
			list = nullptr;
			d = nullptr;
		}
	}

	void printUpload()
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

	void newPC()
	{
		while (true)
		{
			PC* build = new PC;

			cout << "\nEnter a name for your Custom PC: ";
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

	Build startMenu()
	{
		char option = 0;
		while (true && option != 'q')
		{
			cout << "Pick an option: \na: Upload a list of PC Specifications\nb: Create a new PC with Parts\nc: Load the PC Build Roster\nd: Edit the component details\nq: End the program\n\nEnter your choice: ";
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

	vector<Component*> loadAllParts()
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
};

int main()
{
	cout << "Welcome to SwitchMySystem -- Component Analysis & Swap Simulation\n";
	cout << "When entering the name for a custom part, if the name is more then one word, separate the words by a hyphen: -\n\n";
	Build b;
	b.startMenu();

	return 0;
}