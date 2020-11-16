#include "ShopUI.h"

ShopUI::ShopUI()
{
	string index;

	//판매/구매선택
	for (int i = 0; i <= 3; i++)
	{
		index = to_string(i);
		ReadFileString("shop", index, shopList, "GameInfo\\shop.ini");
	}

	//구매목록읽기
	for (int i = 0; i <= 4; i++)
	{
		index = to_string(i);
		ReadFileString("buy", index, buyList, "GameInfo\\shop.ini");
	}

	//판매
	for (int i = 0; i <= 1; i++)
	{
		index = to_string(i);
		ReadFileString("sale", index, salesList, "GameInfo\\shop.ini");
	}
}

void ShopUI::ShopShow()
{
	string s;
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < shopList.size(); i++)
	{
		string s = to_string(i);
		GoToXY(5, 1 + i);
		cout << shopList[s] << endl;
	}
	setlocale(LC_ALL, "");
}

void ShopUI::BuyShow()
{
	for (int i = 0; i < 6; i++)
	{
		GoToXY(5, 1 + i);
		cout << "                                  " << endl;
	}

	string s;
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < buyList.size(); i++)
	{
		string s = to_string(i);
		GoToXY(5, 1 + i);
		cout << buyList[s] << endl;
	}
	setlocale(LC_ALL, "");
}

void ShopUI::SaleShow()
{
	for (int i = 0; i < 6; i++)
	{
		GoToXY(5, 1 + i);
		cout << "                                  " << endl;
	}

	string s;
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < salesList.size(); i++)
	{
		string s = to_string(i);
		GoToXY(5, 1 + i);
		cout << salesList[s];
		if(salesList.size()-1 != i)
			cout << endl;
	}
	setlocale(LC_ALL, "");
}

array<int, 2>& ShopUI::SelectUI()
{
	int x = -1;
	ShopShow();

	GoToXY(1, currentChoice);
	cout << CHOICE;
	
	while (true)
	{
		if (_kbhit())					//키보드누르면
		{
			if (224 == _getch())		//방향키입력받기위해사용
			{
				switch (_getch())			//키입력받고
				{
				case 72:						//위로이동
					if (currentChoice - 1 < 2)
						break;

					GoToXY(1, currentChoice);
					cout << " ";
					GoToXY(1, --currentChoice);
					cout << CHOICE;
					break;

				case 80:							//아래로 이동
					if (currentChoice + 1 > 4)
						break;

					GoToXY(1, currentChoice);
					cout << " ";
					GoToXY(1, ++currentChoice);
					cout << CHOICE;
					break;
				}
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
				break;
		}
	}

	switch (currentChoice - 2)
	{
	case Shop::BUY:
		BuyShow();
		while (true)
		{
			if (_kbhit())					//키보드누르면
			{
				if (224 == _getch())		//방향키입력받기위해사용
				{
					switch (_getch())			//키입력받고
					{
					case 72:			//위로이동
						if (currentChoice - 1 < 2)
							break;

						GoToXY(1, currentChoice);
						cout << " ";
						GoToXY(1, --currentChoice);
						cout << CHOICE;
						break;

					case 80:							//아래로 이동
						if (currentChoice + 1 > 5)
							break;

						GoToXY(1, currentChoice);
						cout << " ";
						GoToXY(1, ++currentChoice);
						cout << CHOICE;
						break;
					}
				}
				if (GetAsyncKeyState(VK_RETURN) & 0x8000)
					break;
			}
		}
		itemChoice[0] = Shop::BUY;
		itemChoice[1] = currentChoice - 2;
		break;

	case Shop::SALE:
		SaleShow();
		itemChoice[0] = Shop::SALE;
		while (x < 0)			//0이상의 숫자만 입력받음
		{
			cin >> x;
			if (!cin)
			{
				GoToXY(10, 2);
				cout << "                   ";
				GoToXY(10, 2);
				cout << "숫자만입력해 : ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				x = -1;
			}
		}

		itemChoice[1] = x - 1;
		break;

	case Shop::EXIT:
		itemChoice[0] = Shop::EXIT;
		break;
	}

	return itemChoice;
}