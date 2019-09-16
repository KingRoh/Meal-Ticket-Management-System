#include "TaxManager.h"

void TaxManager::Tokenize(const string& str, vector<string>& tokens, char delimiters)
{
	istringstream ss(str);
	string item;

	while (getline(ss, item, delimiters))
	{
		tokens.push_back(item);
	}
}

void TaxManager::insertTax(string n, string f, int c)
{
	tList[count] = new Tax(n, f, c);
	count++;
}

void TaxManager::loadFile(string filename)
{
	ifstream inFile(filename);
	string Line;

	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, Line);
			vector<string> tokens;
			Tokenize(Line, tokens, ',');

			tList[count] = new Tax(tokens[0], tokens[1], atoi(tokens[2].c_str()));

			count++;
		}
	}
	else
	{
		cout << "taxÆÄÀÏ ¹Ì¿ÀÇÂ" << endl;
		return;
	}
	inFile.close();
}

void TaxManager::saveFile(string filename)
{
	ofstream outFile(filename);
	for (int i = 0; i < count; i++)
	{
		if (i != count - 1)
			outFile << tList[i]->save() << endl;
		else
			outFile << tList[i]->save();
	}
	outFile.close();
}

Tax TaxManager::getTax(int i)
{
	return *tList[i];
}

int TaxManager::couponSum(string food)
{
	int result = 0;
	for (int i = 0; i < count; i++)
	{
		if (tList[i]->getFood() == food)
		{
			result += tList[i]->getCoupon();
		}
	}
	return result;
}

TaxManager::~TaxManager()
{
	for (int i = 0; i < count; i++)
		delete tList[i];
}