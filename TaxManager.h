#pragma once
#include "Tax.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class TaxManager
{
	Tax *tList[100];
	int count;

public:
	TaxManager() { count = 0; }

	void Tokenize(const string& str, vector<string>& tokens, char delimiters);

	void insertTax(string n, string f, int c);

	void loadFile(string filename);

	void saveFile(string filename);

	Tax getTax(int i);

	int couponSum(string name);

	int getCount() { return count; }

	~TaxManager();
};