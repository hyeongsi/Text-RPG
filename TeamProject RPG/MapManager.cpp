#include "MapManager.h"

void MapManager::GoToXY(const int x, const int y)
{
	COORD pos = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::LoadMap(int num)
{
	string currentDungeon;
	int y = 0;
	char mapPiece;
	int slimeNumber = 0;

	switch (num)
	{
	case 1:
		fcin.open("MapInfo\\dungeon1.txt");
		getline(fcin, currentDungeon);

		for (int y = 0; y < MAP_COL; y++)
		{
			for (int x = 0; x < MAP_ROW; x++)
			{
				fcin.get(mapPiece);
				if (fcin.eof())
					break;
				if (mapPiece == 'p') 
				{
					player->SetPos(x, y);
					mapPiece = ' ';
				}
				else if (mapPiece == 's')		//슬라임이 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
				{
					Slime::AddInstance();
					slime = Slime::GetInstance();
					(*slime)[slimeNumber++]->SetPos(x, y);
					mapPiece = ' ';
				}	
				map[y][x] = mapPiece;
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

	//플레이어가 움직일 수 있는 범위 측정
	LoadCanMovePos();
}

void MapManager::PrintMap()
{
	//원본맵을 출력할 맵에 복사 후
	for (int col = 0; col < MAP_COL; col++)
	{
		for (int row = 0; row < MAP_ROW; row++)
			tempMap[col][row] = map[col][row];
	}

	//캐릭터 정보 가져와서 맵에 동기화
	PrintCharacter(player);
	PrintSlime(slime);

	//출력할 맵 출력
	GoToXY(0, 0);
	for (int y = 0; y < MAP_COL; y++)
	{
		for (int x = 0; x < MAP_ROW; x++)
			cout << tempMap[y][x];
	}
}

void MapManager::PrintCharacter(Character* character)
{
	int option;

	Player* player = dynamic_cast<Player*>(character);
	if (player != NULL)
		option = -1;
	else
		option = 1;

	auto tempPlayerShape = gameInfo->GetShape(option);

	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지[0][0~3] 출력한다.
	//머리 출력
	for (int index = 0; index < SHAPE_ROW; index++)
		tempMap[playerPosY - 2][playerPosX - 1+ index] = tempPlayerShape[0][index];


	//기준점 좌표 y-1 지점으로 이동해 이미지[1][0~3] 출력한다.
	//몸 출력
	for (int index = 0; index < SHAPE_ROW; index++)
		tempMap[playerPosY - 1][playerPosX - 1 + index] = tempPlayerShape[1][index];

	//기준점 좌표 x-1 지점으로 이동해 이미지[2][0~3] 출력한다.
	//다리 출력
	if (!player->GetIsWalking())
	{
		for (int index = 0; index < SHAPE_ROW; index++)
			tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[2][index];
	}
	else
	{
		switch (player->GetWalkCount())
		{
		case 0:
			if (player->GetDir())	//왼쪽이면
			{	//왼쪽1번다리 출력
				for (int index = 0; index < SHAPE_ROW; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[5][index];
			}
			else                    //오른쪽이면
			{	//오른쪽1번다리 출력
				for (int index = 0; index < SHAPE_ROW; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[3][index];
			}
			break;
		case 1:
			if (player->GetDir())	//왼쪽이면
			{	//왼쪽2번다리 출력
				for (int index = 0; index < SHAPE_ROW; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[6][index];
			}
			else                    //오른쪽이면
			{	//오른쪽2번다리 출력
				for (int index = 0; index < SHAPE_ROW; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape[4][index];
			}
			break;
		}
	}
}

void MapManager::PrintSlime(vector<Slime*>* slime)
{
	auto slimeShape = gameInfo->GetShape(1);		//1은 슬라임을 의미 수정하기!
	int slimePosX;
	int slimePosY;

	//슬라임객체수만큼 반복
	for (int i = 0; i < slime->size(); i++)
	{
		slimePosX = (*slime)[i]->GetPos().GetX();
		slimePosY = (*slime)[i]->GetPos().GetY();
		//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지[0][0~3] 출력한다.
		//머리 출력
		for (int index = 0; index < SHAPE_ROW; index++)
			tempMap[slimePosY - 2][slimePosX - 1 + index] = slimeShape[0][index];


		//기준점 좌표 y-1 지점으로 이동해 이미지[1][0~3] 출력한다.
		//몸 출력
		for (int index = 0; index < SHAPE_ROW; index++)
			tempMap[slimePosY - 1][slimePosX - 1 + index] = slimeShape[1][index];

		//기준점 좌표 x-1 지점으로 이동해 이미지[2][0~3] 출력한다.
		//다리 출력
		for (int index = 0; index < SHAPE_ROW; index++)
			tempMap[slimePosY][slimePosX - 1 + index] = slimeShape[2][index];
	}
}

void MapManager::LoadCanMovePos()
{
	//플레이어가 움직일 수 없는 범위 왼쪽 상단 측정
	for (int col = 0; col < MAP_COL; col++)
	{
		for (int row = 0; row < MAP_ROW; row++)
		{
			if (map[col][row] == '*')
			{
				dontMovePos[0].SetX(row);
				dontMovePos[0].SetY(col);
				col = MAP_COL;
				break;
			}
		}
	}
	//플레이어가 움직일 수 없는 범위 오른쪽 하단 측정
	for (int col = MAP_COL - 1; col > 0; col--)
	{
		for (int row = MAP_ROW - 1; row > 0; row--)
		{
			if (map[col][row] == '*')
			{
				dontMovePos[1].SetX(row);
				dontMovePos[1].SetY(col);
				col = 0;
				break;
			}
		}
	}
}

Pos* MapManager::GetDontMovePos()
{
	return dontMovePos;
}
