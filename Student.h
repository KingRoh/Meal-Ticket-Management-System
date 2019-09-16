#pragma once
#include "Person.h"

class Student : public Person
{
	int grade;

public:
	Student() {}

	Student(string n, string a, string p, string m, int g) : Person(n, a, p, m), grade(g) {}

	void setGrade(int l) { grade = l; }

	int getGrade() { return grade; }

	void show();

	string save();
};