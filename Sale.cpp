#pragma warning(disable : 4996)
#include "Sale.h"

Sale::Sale()
{
	PM.loadFile("test_person.csv");
	MM.loadFile("test_menu.csv");
	TM.loadFile("test_tax_" + getToday() + ".csv");
}
void Sale::manageMain()     // 관리모드
{
	int sel;

	while (1)
	{
		cout << "1. 사람관리, 2. 메뉴관리, 3. 판매관리, 4. 이전매뉴 ? ";
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
			cout << "잘못된 입력입니다." << endl;
			break;
		}
	}
}

void Sale::saleMain()    // 판매모드
{
	string name;
	string food;
	int coupon;
	int j;

	cout << "이름: ";
	cin >> name;
	for (int i = 0; i < PM.getCount(); i++)
	{
		if (PM.getPerson(i).getName() == name)
			break;
		if (i == PM.getCount() - 1)
		{
			cout << "등록되지 않은 사람입니다." << endl;
			return;
		}
	}

	cout << "매뉴: ";
	cin >> food;
	for (j = 0; j < MM.getCount(); j++)
	{
		if (MM.getMenu(j).getFood() == food)
			break;
		if (j == MM.getCount() - 1)
		{
			cout << "없는 메뉴입니다." << endl;
			return;
		}
	}

	cout << "수량: ";
	cin >> coupon;
	if (MM.getMenu(j).getCoupon() < coupon)
	{
		cout << "주문수량이 잔여수량보다 많습니다." << endl;
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

void Sale::saleManage()     // 통계
{
	int sel;

	while (1)
	{
		cout << "1. 음식별 판매통계, 2. 사람별 판매통계, 3. 사람별 구매통계, 4. 날짜별 판매통계, 5. 이전매뉴 ? ";
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
			cout << "잘못된 입력입니다." << endl;
			break;
		}
	}
}

void Sale::foodSaleTax()     // 음식별 판매통계 : "음식명, 판매금액, 판매수량, 잔여수량"
{
	cout.setf(ios::left);
	for (int i = 0; i < MM.getCount(); i++)
	{
		cout << "음식명: " << setw(10) << MM.getMenu(i).getFood()
			<< "판매금액: " << setw(10) << (MM.getMenu(i).getPrice() * TM.couponSum(MM.getMenu(i).getFood()))
			<< "판매수량: " << setw(10) << TM.couponSum(MM.getMenu(i).getFood())
			<< "잔여수량: " << setw(10) << MM.getMenu(i).getCoupon() << endl;
	}
}

int Sale::personFoodBuySum(string name, string food)   // 어떤 사람이 어떤 음식에 소비한 금액의 총액
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

int Sale::personCouponBuySum(string name, string food)   // 어떤 사람이 어떤 음식을 구매한 갯수의 총량
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

int Sale::personBuySum(string name)      // 어떤 사람이 소비한 금액의 총액
{
	int result = 0;
	for (int i = 0; i < MM.getCount(); i++)
	{
		result += personFoodBuySum(name, MM.getMenu(i).getFood());
	}
	return result;
}

void Sale::personSaleTax()     // 사람별 판매통계 : "사람이름, 구입금액"
{
	cout.setf(ios::left);
	for (int i = 0; i < PM.getCount(); i++)
	{
		cout << "이름: " << setw(10) << PM.getPerson(i).getName() << "구입금액: " << setw(10) << personBuySum(PM.getPerson(i).getName()) << endl;
	}
}

void Sale::personBuyTax()     // 사람별 구매통계 : "사람이름, (개행 후), 음식명1, 구매갯수, 구매금액"
{
	cout.setf(ios::left);
	for (int i = 0; i < PM.getCount(); i++)
	{
		cout << PM.getPerson(i).getName() << endl;
		for (int j = 0; j < MM.getCount(); j++)
		{
			cout << "               음식명: " << setw(10) << MM.getMenu(j).getFood() <<
				"구매갯수: " << setw(10) << personCouponBuySum(PM.getPerson(i).getName(), MM.getMenu(j).getFood()) <<
				"구매금액: " << setw(10) << personFoodBuySum(PM.getPerson(i).getName(), MM.getMenu(j).getFood()) << endl;
		}
	}
}

void Sale::dateSaleTax()
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".\\*.csv", &fd);  //현재 폴더 내 모든 파일을 찾는다.

	int count = 0;
	string date[10];
	TaxManager dateTM[10];

	if (handle == -1)
	{
		cout << "파일이 없습니다." << endl;
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
			cout << "                       음식명: " << setw(10) << MM.getMenu(j).getFood()
				<< "구매갯수: " << setw(10) << dateTM[i].couponSum(MM.getMenu(j).getFood())
				<< "구매금액: " << setw(10) << (MM.getMenu(j).getPrice() * dateTM[i].couponSum(MM.getMenu(j).getFood())) << endl;
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