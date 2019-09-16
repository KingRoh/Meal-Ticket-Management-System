#include "PersonManager.h"

void PersonManager::personManage()
{
	int sel;
	string name;
	string address; char cs[20];
	string phone;
	string major;
	int lap;
	int grade;

	while (1)
	{
		cout << "1. �������, 2. �л����, 3. �������, 4. ����˻�, 5. �����Ŵ� ? ";
		cin >> sel;

		switch (sel)
		{

		case 1:
			cout << "�̸�: ";
			cin >> name;
			if (isExist(name))
			{
				cout << "�̹� �ִ� ����Դϴ�." << endl;
				break;
			}
			cout << "�ּ�: ";
			cin.getline(cs, 20);
			getline(cin, address);
			cout << "��ȭ��ȣ: ";
			cin >> phone;
			cout << "����: ";
			cin >> major;
			cout << "�����ǹ�ȣ: ";
			cin >> lap;
			insertProfessor(name, address, phone, major, lap);
			saveFile("test_person.csv");
			break;

		case 2:
			cout << "�̸�: ";
			cin >> name;
			if (isExist(name))
			{
				cout << "�̹� �ִ� ����Դϴ�." << endl;
				break;
			}
			cout << "�ּ�: ";
			cin.getline(cs, 20);
			getline(cin, address);
			cout << "��ȭ��ȣ: ";
			cin >> phone;
			cout << "����: ";
			cin >> major;
			cout << "�г�: ";
			cin >> grade;
			insertStudent(name, address, phone, major, grade);
			saveFile("test_person.csv");
			break;

		case 3:
			cout << "�̸�: ";
			cin >> name;
			if (!isExist(name))
			{
				cout << "�������� �ʴ� ����Դϴ�." << endl;
				break;
			}
			Delete(name);
			saveFile("test_person.csv");
			break;

		case 4:
			cout << "�̸�: ";
			cin >> name;
			search(name);
			break;

		case 5:
			return;

		case 6:
			print();
			break;

		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}

void PersonManager::Tokenize(const string& str, vector<string>& tokens, char delimiters)
{
	istringstream ss(str);
	string item;

	while (getline(ss, item, delimiters))
	{
		tokens.push_back(item);
	}
}

void PersonManager::insertProfessor(string n, string a, string p, string m, int l)
{
	pList[count] = new Professor(n, a, p, m, l);
	count++;
}

void PersonManager::insertStudent(string n, string a, string p, string m, int g)
{
	pList[count] = new Student(n, a, p, m, g);
	count++;
}

void PersonManager::print()
{
	for (int i = 0; i < count; i++)
		pList[i]->show();
}

void PersonManager::search(string name)
{
	for (int i = 0; i < count; i++)
	{
		int location = pList[i]->getName().find(name);
		if (location != -1)
			pList[i]->show();
	}
}

bool PersonManager::isExist(string name)
{
	for (int i = 0; i < count; i++)
	{
		if (pList[i]->getName() == name)
		{
			return true;
		}
	}
	return false;
}

void PersonManager::Delete(string name)
{
	for (int i = 0; i < count; i++)
	{
		if (pList[i]->getName() == name)
		{
			pList[i] = pList[count - 1];
			pList[count - 1] = NULL;
			count--;
		}
	}
}

void PersonManager::sort()
{
	Person *temp;
	for (int i = 0; i < count; i++)
	{
		for (int k = 0; k < (count - i - 1); k++)
		{
			if (pList[k]->getName().compare(pList[k + 1]->getName()) > 0)
			{
				temp = pList[k];
				pList[k] = pList[k + 1];
				pList[k + 1] = temp;
			}
		}
	}
	print();
}

void PersonManager::loadFile(string filename)
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
			if (tokens[0] == "S")
				pList[count] = new Student(tokens[1], tokens[2], tokens[3], tokens[4], atoi(tokens[5].c_str()));
			else
				pList[count] = new Professor(tokens[1], tokens[2], tokens[3], tokens[4], atoi(tokens[5].c_str()));
			count++;
		}
	}
	else
	{
		cout << "person���� �̿���" << endl;
		return;
	}
	inFile.close();
}

void PersonManager::saveFile(string filename)
{
	ofstream outFile(filename);
	for (int i = 0; i < count; i++)
	{
		if (i != count - 1)
			outFile << pList[i]->save() << endl;
		else
			outFile << pList[i]->save();
	}
	outFile.close();
}

Person PersonManager::getPerson(int i)
{
	return *pList[i];
}

int PersonManager::getCount()
{
	return count;
}

PersonManager::~PersonManager()
{
	for (int i = 0; i < count; i++)
		delete pList[i];
}