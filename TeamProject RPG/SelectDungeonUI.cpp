#include "SelectDungeonUI.h"

void SelectDungeonUI::Init()
{
	currentChoice = 3;
}

SelectDungeonUI::SelectDungeonUI()
{
	system("cls");
	string index;
	//선택할 던전번호
	for (int i = 0; i <= 4; i++)
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
		cout << select[s];
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
	setlocale(LC_ALL, "");

	Inventory tempInventory = player->GetInventory();
	tempInventory.OpenInventory(true);

	//현재 플레이어 형태 들고와서 출력
	map<string, string> tempPlayerShape = gameInfo->GetShape(MYPLAYER);

	GoToXY(7, 4);
		cout << tempPlayerShape["head"];
	GoToXY(7, 5);
		cout << tempPlayerShape["body"];
	GoToXY(7, 6);
		cout << tempPlayerShape["legs"];

	//현재 플레이어 스텟 받아와서 출력
	GoToXY(15, 2);
	cout << "HP :\t" << player->GetHp();
	GoToXY(15, 3);
	cout << "MP :\t" << player->GetMp();
	GoToXY(15, 4);
	cout << "POWER :\t" << player->GetPower();
	GoToXY(15, 6);
	cout << "EXP :\t" << player->GetExp();
	GoToXY(15, 8);
	cout << "LEVEL :\t" << player->GetLevel();
}

int SelectDungeonUI::Select()
{
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
					if (currentChoice + 2 > 9)
						break;

					GoToXY(57, currentChoice);
					cout << " ";
					currentChoice += 2;
					GoToXY(57, currentChoice);
					cout << CHOICE;
					break;
				}
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)	//스페이스바를 누르면 반복문 탈출
				break;
		}
	}

	if (DUNGEON1 == currentChoice)		//1번던전
		return 1;
	else if (DUNGEON2 == currentChoice)	//2번던전
		return 2;
	else if (DUNGEON3 == currentChoice)	//3번던전
		return 3;
	else if (GAME_EXIT == currentChoice)	//게임종료
		return 0;

	return 0;		//잘못된값
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
