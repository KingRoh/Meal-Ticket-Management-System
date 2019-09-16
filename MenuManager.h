#pragma once
#include "Menu.h"
#include <fstream>
#include <sstream>
#include <vector>

class MenuManager
{
	Menu *mList[10];
	int count;

public:
	MenuManager() { count = 0; }

	void menuManage();

	void Tokenize(const string& str, vector<string>& tokens, char delimiters);

	void insertMenu(string n, int p, int c);

	void insertCoupon(string n, int c);

	bool isExist(string food);

	void Delete(string food);

	void print();

	void loadFile(string filename);

	void saveFile(string filename);

	Menu getMenu(int i);

	Menu getMenu(string food);

	int getCount() { return count; }

	~MenuManager();
};