#include "SelectDungeonUI.h"

SelectDungeonUI::SelectDungeonUI()
{
	system("cls");
	string index;
	//선택할 던전번호
	for (int i = 0; i <= 3; i++)
	{
		index = to_string(i);
		ReadFileString("select", index, select, "GameInfo\\SelectDungeonUI.ini");
	}

	//플레이어 형태에 대한 제목
	ReadFileString("playerExplanation", "playerExplanation", playerExplanation, "GameInfo\\SelectDungeonUI.ini");

	//플레이어를 출력할때 사용할 틀
	for (int i = 0; i <= 6; i++)
	{
		index = to_string(i);
		ReadFileString("playerTemplate", index, playerTemplate, "GameInfo\\SelectDungeonUI.ini");
	}

	//플레이어 형태에 대한 제목
	ReadFileString("inventoryExplanation", "inventoryExplanation", inventoryExplanation, "GameInfo\\SelectDungeonUI.ini");

	//아이템 출력할 틀
	for (int i = 0; i <= 8; i++)
	{
		index = to_string(i);
		ReadFileString("inventory", index, inventory, "GameInfo\\SelectDungeonUI.ini");
	}
}

void SelectDungeonUI::Show()
{
	string index;
	setlocale(LC_ALL, "ko_KR.UTF8");
	//선택할 요소들 출력
	for (int i = 0; i < select.size(); i++)
	{
		string s = to_string(i);
		GoToXY(60, 1 + (i * 2));
		cout << select[s] << endl;
	}

	//플레이어에 대한 설명 출력
	GoToXY(2, 1);
	cout << playerExplanation;

	//플레이어 출력할 틀을 출력
	for (int i = 0; i < playerTemplate.size(); i++)
	{
		GoToXY(3, 2 + i);
		index = to_string(i);
		cout << playerTemplate[index];
	}

	//인벤토리에 대한 설명 출력
	GoToXY(7, 14);
	cout << inventoryExplanation;

	//아이템 출력할 틀 출력
	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 15 + i);
		index = to_string(i);
		cout << inventory[index];
	}
	setlocale(LC_ALL, "");

	//현재 플레이어 형태 들고와서 출력
	auto tempPlayerShape = gameInfo->GetShape(MYPLAYER);
	for (int i = 0; i < 3; i++)
	{
		GoToXY(7, 4 + i);
		cout << tempPlayerShape[i];
	}

	//현재 플레이어 스텟 받아와서 출력
	playerStat["hp"] = player->GetHp();
	playerStat["power"] = player->GetPower();
	GoToXY(15, 4);
	cout << "HP : " << playerStat["hp"];
	GoToXY(15, 6);
	cout << "POWER : " << playerStat["power"];
}

int SelectDungeonUI::Select()
{
	Show();
	GoToXY(57, currentChoice);
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
					if (currentChoice - 2 < 3)
						break;

					GoToXY(57, currentChoice);
					cout << " ";
					currentChoice -= 2;
					GoToXY(57, currentChoice);
					cout << CHOICE;
					break;

				case 80:							//아래로 이동
					if (currentChoice + 2 > 7)
						break;

					GoToXY(57, currentChoice);
					cout << " ";
					currentChoice += 2;
					GoToXY(57, currentChoice);
					cout << CHOICE;
					break;
				}
			}
			else
				break;
		}
	}

	if (currentChoice == DUNGEON1)		//1번던전
		return 1;
	else if (currentChoice == DUNGEON2)	//2번던전
		return 2;
	else if (currentChoice == DUNGEON3)	//3번던전
		return 3;

	return -1;		//잘못된값
}

SelectDungeonUI::~SelectDungeonUI()
{
	auto selectIterator = select.begin();
	while (selectIterator != select.end())
	{
		select.erase(selectIterator++);
	}

	auto playerTemplateIterator = playerTemplate.begin();
	while (playerTemplateIterator != playerTemplate.end())
	{
		playerTemplate.erase(playerTemplateIterator++);
	}

	auto inventoryIterator = inventory.begin();
	while (inventoryIterator != inventory.end())
	{
		inventory.erase(inventoryIterator++);
	}
}
