#include "Sale.h"

int main()
{
	int sel;
	Sale s;

	while (1)
	{
		cout << "1. 관리모드, 2. 판매모드, 3. 종료 ? ";
		cin >> sel;

		switch (sel)
		{
		case 1:
			s.manageMain();
			break;

		case 2:
			s.saleMain();
			break;

		case 3:
			return 0;
			break;

		default:
			cout << "잘못된 입력입니다." << endl;
			break;
		}
	}
}