#pragma once
#include "Person.h"

class Professor : public Person
{
	int lap;

public:
	Professor() { }

	Professor(string n, string a, string p, string m, int l) : Person(n, a, p, m), lap(l) {}

	void setLap(int l) { lap = l; }

	int getLap() { return lap; }

	void show();

	string save();
};