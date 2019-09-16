#pragma once
#include "Person.h"
#include "Professor.h"
#include "Student.h"
#include <fstream>
#include <sstream>
#include <vector>

class PersonManager
{
	Person *pList[10];
	int count;

public:
	PersonManager() { count = 0; }

	void personManage();

	void Tokenize(const string& str, vector<string>& tokens, char delimiters);

	void insertProfessor(string n, string a, string p, string m, int l);

	void insertStudent(string n, string a, string p, string m, int g);

	void print();

	void search(string name);

	bool isExist(string name);

	void Delete(string name);

	void sort();

	void loadFile(string filename);

	void saveFile(string filename);

	Person getPerson(int i);

	int getCount();

	~PersonManager();
};