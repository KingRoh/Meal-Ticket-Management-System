#pragma once
#include <string>

using namespace std;

class Tax
{
	string name;
	string food;
	int coupon;

public:
	Tax() {}

	Tax(string n, string f, int c) { name = n; food = f; coupon = c; }

	void setName(string n) { name = n; }

	string getName() { return name; }

	void setFood(string f) { food = f; }

	string getFood() { return food; }

	void setCoupon(int c) { coupon = c; }

	int getCoupon() { return coupon; }

	string save();
};