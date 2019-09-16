#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Menu
{
	string food;
	int price;
	int coupon;

public:
	Menu() {}

	Menu(string n, int p, int c) { food = n; price = p; coupon = c; }

	void setFood(string n) { food = n; }

	string getFood() { return food; }

	void setPrice(int p) { price = p; }

	int getPrice() { return price; }

	void setCoupon(int c) 
	{ 
		coupon = c; 
	}

	int getCoupon() 
	{ 
		return coupon; 
	}

	void show();

	string save();
};