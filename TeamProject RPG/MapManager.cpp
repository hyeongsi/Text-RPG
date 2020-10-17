#include "MapManager.h"

void MapManager::GoToXY(const int x, const int y)
{
	COORD pos = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::PrintCharacter(Character* character)
{
	int option;

	Player* player = dynamic_cast<Player*>(character);
	if (player != NULL)
		option = 1;
	else
		option = 2;

	auto tempPlayerShape = gameInfo->GetShape(option);

	//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지[0][3] 출력한다.
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY() - 2);
	for (int index = 0; index < 3; index++)
		cout << tempPlayerShape[0][index];

	//기준점 좌표 y+1 지점으로 이동해 이미지[1][3] 출력한다.
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY() - 1);
	for (int index = 0; index < 3; index++)
		cout << tempPlayerShape[1][index];

	//기준점 좌표 y+1 지점으로 이동해 이미지[2][3] 출력한다.
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY());
	for (int index = 0; index < 3; index++)
		cout << tempPlayerShape[2][index];
}

void MapManager::LoadMap(int num)
{
	string currentDungeon;
	int y = 0;
	char c;

	switch (num)
	{
	case 1:
		fcin.open("MapInfo\\dungeon1.txt");
		getline(fcin, currentDungeon);

		for (int y = 0; y < MAP_COL; y++)
		{
			for (int x = 0; x < MAP_ROW; x++)
			{
				fcin.get(c);
				if (fcin.eof())
					break;
				if (c == 'p') 
				{
					player->SetPos(x, y);
					c = ' ';
				}
					
				map[y][x] = c;
				
			}
		}
		break;

	case 2:
		fcin.open("MapInfo\\dungeon2.txt");
		getline(fcin, currentDungeon);
		break;

	default:
		cout << "맵 로드 오류!!";
		break;
	}
}


void MapManager::PrintMap()
{
	GoToXY(0, 0);
	for (int y = 0; y < MAP_COL; y++)
	{
		for (int x = 0; x < MAP_ROW; x++)
			cout << map[y][x];
	}


	PrintCharacter(player);
}

void MapManager::CheckOutOfMap()
{

}
