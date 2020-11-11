#include "ShopUI.h"

ShopUI::ShopUI()
{
	string index;

	//판매목록읽기
	for (int i = 0; i <= 5; i++)
	{
		index = to_string(i);
		ReadFileString("npc", index, salesList, "GameInfo\\npc.ini");
	}
}

void ShopUI::Show()
{
	string s;
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < salesList.size(); i++)
	{
		string s = to_string(i);
		GoToXY(5, 1 + i);
		cout << salesList[s] << endl;
	}
	setlocale(LC_ALL, "");
}

int ShopUI::SelectUI()
{
	Show();
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
				case 72:			//위로이동
					if (currentChoice - 2 < 1)
						break;

					GoToXY(1, currentChoice);
					cout << " ";
					currentChoice--;
					GoToXY(1, currentChoice);
					cout << CHOICE;
					break;

				case 80:							//아래로 이동
					if (currentChoice + 2 > 7)
						break;

					GoToXY(1, currentChoice);
					cout << " ";
					currentChoice++;
					GoToXY(1, currentChoice);
					cout << CHOICE;
					break;
				}
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
				break;
		}
	}

	//-2하는이유는 아이템번호와 선택한 번호의 차이가 2라서 맞춰주기위함
	return currentChoice - 2;
}