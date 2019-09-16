#include"Menu.h"

void Menu::show()
{
	cout.setf(ios::left);
	cout << setw(10) << food << setw(10) << price << setw(10) << coupon << endl;
}

string Menu::save()
{
	return food + "," + to_string(price) + "," + to_string(coupon);
}