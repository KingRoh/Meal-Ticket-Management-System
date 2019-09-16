#include "Person.h"

Person::Person(string n, string a, string p, string m)
{
	name = n;
	address = a;
	phone = p;
	major = m;
}

void Person::show()
{
	cout.setf(ios::left);
	cout << setw(10) << name << setw(20) << address << setw(20) << phone << setw(10) << major;
}

string Person::save()
{
	return "S," + name + "," + address + "," + phone + "," + major;
}