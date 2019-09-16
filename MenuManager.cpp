#include "MenuManager.h"

void MenuManager::menuManage()
{
	int sel;
	string food;
	int price;
	int coupon;

	while (1)
	{
		cout << "1. �޴����, 2. �޴�����, 3. �ı��߰�, 4. �����Ŵ� ? ";
		cin >> sel;

		switch (sel)
		{
		case 1:
			cout << "�޴���: ";
			cin >> food;
			if (isExist(food))
			{
				cout << "�̹� �ִ� �Ŵ��Դϴ�." << endl;
				break;
			}
			cout << "����: ";
			cin >> price;
			cout << "����: ";
			cin >> coupon;
			insertMenu(food, price, coupon);
			saveFile("test_menu.csv");
			break;

		case 2:
			cout << "�̸�: ";
			cin >> food;
			if (!isExist(food))
			{
				cout << "���� �Ŵ��Դϴ�." << endl;
				break;
			}
			for (int i = 0; i < count; i++)
			{
				if (mList[i]->getFood() == food)
				{
					if (mList[i]->getCoupon() > 0)
					{
						cout << "���� �ܿ������� �����ֽ��ϴ�." << endl;
						break;
					}
					else if (mList[i]->getCoupon() == 0)
					{
						Delete(food);
						cout << food << "�� �����Ǿ����ϴ�." << endl;
						saveFile("test_menu.csv");
						break;
					}
				}
			}
			break;

		case 3:
			cout << "�޴���: ";
			cin >> food;
			if (!isExist(food))
			{
				cout << "���� �Ŵ��Դϴ�." << endl;
				break;
			}
			cout << "����: ";
			cin >> coupon;
			insertCoupon(food, coupon);
			saveFile("test_menu.csv");
			break;

		case 4:
			return;

		case 5:
			print();
			break;

		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}

void MenuManager::Tokenize(const string& str, vector<string>& tokens, char delimiters)
{
	istringstream ss(str);
	string item;

	while (getline(ss, item, delimiters))
	{
		tokens.push_back(item);
	}
}

void MenuManager::insertMenu(string f, int p, int c)
{
	mList[count] = new Menu(f, p, c);
	count++;
}

void MenuManager::insertCoupon(string f, int c)
{
	for (int i = 0; i < count; i++)
	{
		if (mList[i]->getFood() == f)
		{
			mList[i]->setCoupon(mList[i]->getCoupon() + c);
		}
	}
}

bool MenuManager::isExist(string food)
{
	for (int i = 0; i < count; i++)
	{
		if (mList[i]->getFood() == food)
		{
			return true;
		}
	}
	return false;
}

void MenuManager::Delete(string food)
{
	for (int i = 0; i < count; i++)
	{
		if (mList[i]->getFood() == food)
		{
			mList[i] = mList[count - 1];
			mList[count - 1] = NULL;
			count--;
		}
	}
}

void MenuManager::print()
{
	for (int i = 0; i < count; i++)
		mList[i]->show();
}

void MenuManager::loadFile(string filename)
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

			mList[count] = new Menu(tokens[0], atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));

			count++;
		}
	}
	else
	{
		cout << "menu���� �̿���" << endl;
		return;
	}
	inFile.close();
}

void MenuManager::saveFile(string filename)
{
	ofstream outFile(filename);
	for (int i = 0; i < count; i++)
	{
		if (i != count - 1)
			outFile << mList[i]->save() << endl;
		else
			outFile << mList[i]->save();
	}
	outFile.close();
}

Menu MenuManager::getMenu(int i)
{
	return *mList[i];
}

Menu MenuManager::getMenu(string food)
{
	for (int i = 0; i < count; i++)
	{
		if (mList[i]->getFood() == food)
			return *mList[i];
	}
}

MenuManager::~MenuManager()
{
	for (int i = 0; i < count; i++)
		delete mList[i];
}