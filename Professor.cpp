#include "Professor.h"

void Professor::show()
{
	Person::show();
	cout << setw(10) << lap << endl;
}

string Professor::save()
{
	string l = to_string(lap);
	return Person::save() + "," + l;
}