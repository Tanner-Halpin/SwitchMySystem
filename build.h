#ifndef BUILD_H
#define BUILD_H
#include "parts.h"

bool operator==(const Component& p1, const Component& p2);

struct PC
{
	string name;
	Component* CPU = NULL; Component* GPU = NULL; Component* SSD = NULL; Component* RAM = NULL; Component* Motherboard = NULL; Component* PSU = NULL;
};
ostream& operator<<(ostream& out, PC& p);
istream& operator>>(istream& in, PC& b);

class Build : public Parts
{
protected:
	string m_name;
	vector<PC> buildRoster;

public:
	bool isBuildEqual(Component& p1, Component& p2);
	void addAttribute(int choice);
	void loadParts();
	void printUpload();
	void newPC();
	Build startMenu();
	vector<Component*> loadAllParts();
};

#endif // !BUILD_H