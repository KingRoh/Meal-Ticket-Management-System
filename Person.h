#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Person
{
	string name;
	string address;
	string phone;
	string major;

public:
	Person() {}

	Person(string n, string a, string p, string m);

	void setName(string n) { name = n; }

	void setAddress(string a) { address = a; }

	void setPhone(string p) { phone = p; }

	void setMajor(string m) { major = m; }


	string getName() { return name; }

	string getAddress() { return address; }

	string getPhone() { return phone; }

	string getMajor() { return major; }


	virtual void show();

	virtual string save();
};