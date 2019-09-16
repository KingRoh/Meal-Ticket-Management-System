#pragma warning(disable : 4996)
#include "Sale.h"

Sale::Sale()
{
	PM.loadFile("test_person.csv");
	MM.loadFile("test_menu.csv");
	TM.loadFile("test_tax_" + getToday() + ".csv");
}
void Sale::manageMain()     // �������
{
	int sel;

	while (1)
	{
		cout << "1. �������, 2. �޴�����, 3. �ǸŰ���, 4. �����Ŵ� ? ";
		cin >> sel;
		switch (sel)
		{
		case 1:
			PM.personManage();
			break;

		case 2:
			MM.menuManage();
			break;

		case 3:
			saleManage();
			break;

		case 4:
			return;

		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}

void Sale::saleMain()    // �ǸŸ��
{
	string name;
	string food;
	int coupon;
	int j;

	cout << "�̸�: ";
	cin >> name;
	for (int i = 0; i < PM.getCount(); i++)
	{
		if (PM.getPerson(i).getName() == name)
			break;
		if (i == PM.getCount() - 1)
		{
			cout << "��ϵ��� ���� ����Դϴ�." << endl;
			return;
		}
	}

	cout << "�Ŵ�: ";
	cin >> food;
	for (j = 0; j < MM.getCount(); j++)
	{
		if (MM.getMenu(j).getFood() == food)
			break;
		if (j == MM.getCount() - 1)
		{
			cout << "���� �޴��Դϴ�." << endl;
			return;
		}
	}

	cout << "����: ";
	cin >> coupon;
	if (MM.getMenu(j).getCoupon() < coupon)
	{
		cout << "�ֹ������� �ܿ��������� �����ϴ�." << endl;
		return;
	}
	else
	{
		TM.insertTax(name, food, coupon);
		TM.saveFile("test_tax_" + getToday() + ".csv");

		MM.insertCoupon(food, -coupon);
		MM.saveFile("test_menu.csv");
	}
}

void Sale::saleManage()     // ���
{
	int sel;

	while (1)
	{
		cout << "1. ���ĺ� �Ǹ����, 2. ����� �Ǹ����, 3. ����� �������, 4. ��¥�� �Ǹ����, 5. �����Ŵ� ? ";
		cin >> sel;
		switch (sel)
		{
		case 1:
			foodSaleTax();
			break;

		case 2:
			personSaleTax();
			break;

		case 3:
			personBuyTax();
			break;

		case 4:
			dateSaleTax();
			break;

		case 5:
			return;

		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}

void Sale::foodSaleTax()     // ���ĺ� �Ǹ���� : "���ĸ�, �Ǹűݾ�, �Ǹż���, �ܿ�����"
{
	cout.setf(ios::left);
	for (int i = 0; i < MM.getCount(); i++)
	{
		cout << "���ĸ�: " << setw(10) << MM.getMenu(i).getFood()
			<< "�Ǹűݾ�: " << setw(10) << (MM.getMenu(i).getPrice() * TM.couponSum(MM.getMenu(i).getFood()))
			<< "�Ǹż���: " << setw(10) << TM.couponSum(MM.getMenu(i).getFood())
			<< "�ܿ�����: " << setw(10) << MM.getMenu(i).getCoupon() << endl;
	}
}

int Sale::personFoodBuySum(string name, string food)   // � ����� � ���Ŀ� �Һ��� �ݾ��� �Ѿ�
{
	int result = 0;
	for (int i = 0; i < TM.getCount(); i++)
	{
		if (TM.getTax(i).getName() == name && TM.getTax(i).getFood() == food)
		{
			result += (TM.getTax(i).getCoupon() * MM.getMenu(food).getPrice());
		}
	}
	return result;
}

int Sale::personCouponBuySum(string name, string food)   // � ����� � ������ ������ ������ �ѷ�
{
	int result = 0;
	for (int i = 0; i < TM.getCount(); i++)
	{
		if (TM.getTax(i).getName() == name && TM.getTax(i).getFood() == food)
		{
			result += TM.getTax(i).getCoupon();
		}
	}
	return result;
}

int Sale::personBuySum(string name)      // � ����� �Һ��� �ݾ��� �Ѿ�
{
	int result = 0;
	for (int i = 0; i < MM.getCount(); i++)
	{
		result += personFoodBuySum(name, MM.getMenu(i).getFood());
	}
	return result;
}

void Sale::personSaleTax()     // ����� �Ǹ���� : "����̸�, ���Աݾ�"
{
	cout.setf(ios::left);
	for (int i = 0; i < PM.getCount(); i++)
	{
		cout << "�̸�: " << setw(10) << PM.getPerson(i).getName() << "���Աݾ�: " << setw(10) << personBuySum(PM.getPerson(i).getName()) << endl;
	}
}

void Sale::personBuyTax()     // ����� ������� : "����̸�, (���� ��), ���ĸ�1, ���Ű���, ���űݾ�"
{
	cout.setf(ios::left);
	for (int i = 0; i < PM.getCount(); i++)
	{
		cout << PM.getPerson(i).getName() << endl;
		for (int j = 0; j < MM.getCount(); j++)
		{
			cout << "               ���ĸ�: " << setw(10) << MM.getMenu(j).getFood() <<
				"���Ű���: " << setw(10) << personCouponBuySum(PM.getPerson(i).getName(), MM.getMenu(j).getFood()) <<
				"���űݾ�: " << setw(10) << personFoodBuySum(PM.getPerson(i).getName(), MM.getMenu(j).getFood()) << endl;
		}
	}
}

void Sale::dateSaleTax()
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".\\*.csv", &fd);  //���� ���� �� ��� ������ ã�´�.

	int count = 0;
	string date[10];
	TaxManager dateTM[10];

	if (handle == -1)
	{
		cout << "������ �����ϴ�." << endl;
		return;
	}

	while (result != -1)
	{
		if (count > 1)
		{
			date[count - 2] = fd.name;
			dateTM[count - 2].loadFile(date[count - 2]);
		}
		result = _findnext(handle, &fd);
		count++;
	}

	cout.setf(ios::left);
	
	for (int i = 0; i < count - 2; i++)
	{
		cout << date[i].substr(9) << endl;
		
		for (int j = 0; j < MM.getCount(); j++)
		{
			cout << "                       ���ĸ�: " << setw(10) << MM.getMenu(j).getFood()
				<< "���Ű���: " << setw(10) << dateTM[i].couponSum(MM.getMenu(j).getFood())
				<< "���űݾ�: " << setw(10) << (MM.getMenu(j).getPrice() * dateTM[i].couponSum(MM.getMenu(j).getFood())) << endl;
		}
	}
	_findclose(handle);
}
string Sale::getToday()
{
	tm* datetime;
	time_t t;

	t = time(NULL);
	datetime = localtime(&t);

	string today = to_string(datetime->tm_year + 1900) + "-" + to_string(datetime->tm_mon + 1) + "-" + to_string(datetime->tm_mday);

	return today;
}
//Sale::~Sale()
//{
//	PM.saveFile();
//	MM.saveFile();
//	TM.saveFile();
//}