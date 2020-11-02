#include "EscMenuUI.h"

EscMenuUI::EscMenuUI()
{
	isOpen = false;
	currentSelectPosition = 1;

	delay.SetDelayTime(100);
}

void EscMenuUI::ClearEscSelectMenu()
{
	GoToXY(70, 31);
	cout << "  " << endl;
	GoToXY(70, 33);
	cout << "  " << endl;
	GoToXY(70, 36);
	cout << "  " << endl;
}

void EscMenuUI::ClearAllMenu()
{
	GoToXY(70, 31);
	cout << "                                    " << endl;
	GoToXY(70, 33);
	cout << "                                    " << endl;
	GoToXY(70, 34);
	cout << "                                    " << endl;
	GoToXY(70, 35);
	cout << "                                    " << endl;
	GoToXY(70, 36);
	cout << "                                    " << endl;
}

const int EscMenuUI::OpenEscMenu()
{
	currentSelectPosition = 1;
	GoToXY(70, 31);
	cout << "☞" << endl;
	GoToXY(74, 31);
	cout << "나가기" << endl;
	
	GoToXY(74, 33);
	cout << "아이템사용" << endl;

	GoToXY(74, 36);
	cout << "취소" << endl;

	return SelectEscMenu();
}

const int EscMenuUI::SelectEscMenu()
{
	if (GetAsyncKeyState(VK_RETURN) && 0x0001);//이걸로 버퍼 제거
	while (1)
	{
		if (!delay.CheckEndDelay())					//선택자 이동 딜레이
			continue;

		if (GetAsyncKeyState(VK_UP) && 0x8000)		//위
		{
			currentSelectPosition -= 1;
			ClearEscSelectMenu();
		}
		if (GetAsyncKeyState(VK_DOWN) && 0x8000)	//아래
		{
			currentSelectPosition += 1;
			ClearEscSelectMenu();
		}

		if (currentSelectPosition < 1)
			currentSelectPosition = 1;
		if (currentSelectPosition > 3)
			currentSelectPosition = 3;

		switch (currentSelectPosition)
		{
		case 1:
			GoToXY(70, 31);
			cout << "☞" << endl;
			break;
		case 2:
			GoToXY(70, 33);
			cout << "☞" << endl;
			break;
		case 3:
			GoToXY(70, 36);
			cout << "☞" << endl;
			break;
		}

		if (GetAsyncKeyState(VK_RETURN) && 0x8000)	//엔터
		{
			int selectItem = NOTHING;

			switch (currentSelectPosition)
			{
			case 1:
				ClearAllMenu();
				return EXIT_ESC_MENU;
			case 2:
				GoToXY(70, 34);
				cout << "사용할 아이템 번호(0 ~ 16) : ";
				getchar();	//버퍼제거
				GoToXY(98, 34);
				cin >> selectItem;
				getchar();	//버퍼제거
				Sleep(50);

				if ((NOTHING != selectItem) && (0 <= selectItem) && (16 >= selectItem))
				{
					GoToXY(70, 35);
					cout << selectItem << "번 아이템 사용!";
					Sleep(200);
					ClearAllMenu();
					return selectItem;
				}
				else
				{
					GoToXY(70, 35);
					cout << "0 ~ 16 까지 아이템번호를 입력해주세요";
					Sleep(50);
					ClearAllMenu();
				}
			case 3:
				ClearAllMenu();
				return NOTHING;
			}

			
		}
	}
}

