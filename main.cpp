#include "Sale.h"

int main()
{
	int sel;
	Sale s;

	while (1)
	{
		cout << "1. �������, 2. �ǸŸ��, 3. ���� ? ";
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
			cout << "�߸��� �Է��Դϴ�." << endl;
			break;
		}
	}
}