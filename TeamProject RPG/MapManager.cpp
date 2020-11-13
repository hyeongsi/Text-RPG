#include "MapManager.h"

void MapManager::Init()
{
	monsterNumber = 0;		//몬스터들의 수가 들어갈 변수
	monster = nullptr;
}

void MapManager::GoToXY(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::LoadMap(const int& num)
{
	string currentDungeon;
	char mapPiece;

	switch (num)
	{
	case 1:
		fcin.open("MapInfo\\dungeon1.txt");
		getline(fcin, currentDungeon);
		break;
	case 2:
		fcin.open("MapInfo\\dungeon2.txt");
		getline(fcin, currentDungeon);
		break;
	case 3:
		fcin.open("MapInfo\\dungeon3.txt");
		getline(fcin, currentDungeon);
		break;
	default:
		cout << "맵 로드 오류!!";
		exit(0);
		break;
	}

	for (int y = 0; y < MAP_ROW; y++)
	{
		for (int x = 0; x < MAP_COL; x++)
		{
			fcin.get(mapPiece);
			if (fcin.eof())
				break;
			if (mapPiece == 'p')
			{
				player = Player::GetInstance();
				player->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 'n')		//NPC좌표넣기
			{
				npc->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 's')		//슬라임이 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Slime::AddInstance();
				monster = Monster::GetInstance();
				(*monster)[monsterNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 'o')		//오크가 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Oak::AddInstance();
				monster = Monster::GetInstance();
				(*monster)[monsterNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 't')		//탱크가 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Tank::AddInstance();
				monster = Monster::GetInstance();
				(*monster)[monsterNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 'e')
			{
				exitPosition.SetX(x);
				exitPosition.SetY(y);
				mapPiece = '+';
			}
			map[y][x] = mapPiece;
		}
	}
	//플레이어가 움직일 수 있는 범위 측정
	LoadCanMovePos();

	fcin.close();
}

const Pos& MapManager::GetExitPosition()
{
	return exitPosition;
}

void MapManager::PrintMap(bool isOpenInventory)
{
	//원본맵을 출력할 맵에 복사 후
	for (int col = 0; col < MAP_ROW; col++)
	{
		for (int row = 0; row < MAP_COL; row++)
			tempMap[col][row] = map[col][row];
	}

	PrintItemBox();

	for (auto monsterIterator : *monster)
		PrintMonster(monsterIterator);

	PrintNPC();
	PrintCharacter(player);
	PrintWeapon(player->GetHoldWeapon());

	if (isOpenInventory)
	{
		player->OpenInventory();
	}

	//플레이어 피격시 이펙트표시를 위해 사용
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();

	//출력할 맵 출력
	GoToXY(0, 0);
	for (int y = 0; y < MAP_ROW; y++)
	{
		for (int x = 0; x < MAP_COL; x++)
		{
			if (player->GetIsInvincibility())		//현재 무적시간이면 플레이어 색깔 빨간색으로출력
			{
				if ((playerXPosition >= x - 1 && playerXPosition <= x + 1) && (playerYPosition >= y && playerYPosition <= y + 2))
					SetColor(4, 0);
			}
			else if(player->IsActivePowerBuff())		//버프 지속 시간일 때
			{
				if ((playerXPosition >= x - 1 && playerXPosition <= x + 1) && (playerYPosition >= y && playerYPosition <= y + 2))
					SetColor(6, 0);
			}

			cout << tempMap[y][x];

			SetColor(15, 0);
		}
	}
}

void MapManager::PrintCharacter(Character* character)
{
	auto tempPlayerShape = gameInfo->GetShape(MYPLAYER);

	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if (player->GetIsPickUp())	//줍기 모션 실행
	{
		if (RIGHT == player->GetDir())
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY - 2][playerPosX - 1 + index] = tempPlayerShape["pickupHead"][index];
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY - 1][playerPosX - 1 + index] = tempPlayerShape["pickupBody"][index];
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["pickupLegs"][index];
		}
		else if(LEFT == player->GetDir())
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY - 2][playerPosX + 1 - index] = tempPlayerShape["pickupHead"][index];
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY - 1][playerPosX - 1 + index] = tempPlayerShape["pickupBody"][index];
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[playerPosY][playerPosX + index] = tempPlayerShape["pickupLegs"][index];
		}
		
		return;
	}

	//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지[0][0~3] 출력한다.
	//머리 출력
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[playerPosY - 2][playerPosX - 1 + index] = tempPlayerShape["head"][index];

	//기준점 좌표 y-1 지점으로 이동해 이미지[1][0~3] 출력한다.
	//몸 출력
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[playerPosY - 1][playerPosX - 1 + index] = tempPlayerShape["body"][index];

	//기준점 좌표 x-1 지점으로 이동해 이미지[2][0~3] 출력한다.
	//다리 출력
	if (!player->GetIsWalking())
	{
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["legs"][index];
	}
	else
	{
		switch (player->GetWalkCount())
		{
		case 0:
			if (LEFT == player->GetDir())
			{	//왼쪽1번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["walkingLeft1"][index];
			}
			else if (RIGHT == player->GetDir())
			{	//오른쪽1번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["walkingRight1"][index];
			}
			break;
		case 1:
			if (LEFT == player->GetDir())
			{	//왼쪽2번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["walkingLeft2"][index];
			}
			else if(RIGHT == player->GetDir())
			{	//오른쪽2번다리 출력
				for (int index = 0; index < SHAPE_COL; index++)
					tempMap[playerPosY][playerPosX - 1 + index] = tempPlayerShape["walkingRight2"][index];
			}
			break;
		}
	}
}

void MapManager::PrintWeapon(string weapon)
{
	if (player->GetIsPickUp())
		return;

	string tempWeaponShape, tempWeaponSwingShape;
	tempWeaponShape = gameInfo->GetItemShape(weapon,WEAPON);
	tempWeaponSwingShape = gameInfo->GetItemShape(weapon, WEAPON_SWING_SHAPE);

	if (tempWeaponShape.size() == 0)
		return;

	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if (player->GetIsAttacking() && RIGHT == player->GetDir())	//공격모션 출력
	{
		for (int index = 0; index < tempWeaponSwingShape.size(); index++)
			tempMap[playerPosY - 1][playerPosX + 3 + index] = tempWeaponSwingShape[index];
	}
	else if (player->GetIsAttacking() && LEFT == player->GetDir())
	{
		for (int index = 0; index < tempWeaponSwingShape.size(); index++)
			tempMap[playerPosY - 1][playerPosX - 3 + index] = tempWeaponSwingShape[(tempWeaponSwingShape.size()-1)-index];
	}
	else if (!player->GetIsAttacking() && RIGHT == player->GetDir())	//스탠드모션 출력
	{
		for (int index = 0; index < tempWeaponShape.size(); index++)
			tempMap[playerPosY - 2 + index][playerPosX + 2] = tempWeaponShape[index];
	}
	else if (!player->GetIsAttacking() && LEFT == player->GetDir())
	{
		for (int index = 0; index < tempWeaponShape.size(); index++)
			tempMap[playerPosY - 2 + index][playerPosX - 2] = tempWeaponShape[index];
	}
}

void MapManager::PrintMonster(Monster* monster)
{
	std::map<string, string> monsterShape;
	int monsterPosX = monster->GetPos().GetX();
	int monsterPosY = monster->GetPos().GetY();

	//각 자료형에 맞게 몬스터UI불러오기
	if (typeid(*monster) == typeid(Slime))
		monsterShape = gameInfo->GetShape(SLIME);
	else if (typeid(*monster) == typeid(Oak))
		monsterShape = gameInfo->GetShape(OAK);
	else if (typeid(*monster) == typeid(Tank))
		monsterShape = gameInfo->GetShape(TANK);

	if (typeid(*monster) == typeid(Tank))
	{
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[monsterPosY - 2][monsterPosX - 1 + index] = monsterShape["head"][index];

		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[monsterPosY][monsterPosX - 1 + index] = monsterShape["legs"][index];

		//플레이어위치에따라 달라지는 탱크의 형태
		if (player->GetPos().GetX() - (*monster).GetPos().GetX() < 0)
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[monsterPosY - 1][monsterPosX - 1 + index] = monsterShape["bodyR"][index];
		}
		else if(player->GetPos().GetX() - (*monster).GetPos().GetX() >= 0)
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[monsterPosY - 1][monsterPosX - 1 + index] = monsterShape["bodyL"][index];
		}
	}
	else
	{
		//머리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[monsterPosY - 2][monsterPosX - 1 + index] = monsterShape["head"][index];

		//몸 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[monsterPosY - 1][monsterPosX - 1 + index] = monsterShape["body"][index];

		//다리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[monsterPosY][monsterPosX - 1 + index] = monsterShape["legs"][index];
	}

}

void MapManager::PrintItemBox()
{
	auto itemBoxShape = gameInfo->GetShape(ITEMBOX);
	int itemPositionX = 0;
	int itemPositionY = 0;

	for (auto itemPositions : (*Monster::itemPosition))
	{
		itemPositionX = itemPositions.GetX();
		itemPositionY = itemPositions.GetY();

		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[itemPositionY - 2][itemPositionX - 1 + index] = itemBoxShape["head"][index];

		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[itemPositionY - 1][itemPositionX - 1 + index] = itemBoxShape["body"][index];

		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[itemPositionY][itemPositionX - 1 + index] = itemBoxShape["legs"][index];
	}

}

void MapManager::PrintNPC()
{
	auto NPCShape = gameInfo->GetShape(NPC);
	int npcXPosition = npc->GetPos().GetX();
	int npcYPosition = npc->GetPos().GetY();

	//NPC글자출력
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[npcYPosition - 2][npcXPosition - 1 + index] = NPCShape["info"][index];
	//머리
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[npcYPosition - 0][npcXPosition - 1 + index] = NPCShape["head"][index];
	//몸통
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[npcYPosition + 1][npcXPosition - 1 + index] = NPCShape["body"][index];
	//다리
	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[npcYPosition + 2][npcXPosition - 1 + index] = NPCShape["legs"][index];
}

void MapManager::LoadCanMovePos()
{
	//플레이어가 움직일 수 없는 범위 왼쪽 상단 측정
	for (int row = 0; row < MAP_ROW; row++)
	{
		for (int col = 0; col < MAP_COL; col++)
		{
			if (map[row][col] == '*')
			{
				dontMovePos[0].SetX(col);
				dontMovePos[0].SetY(row);
				row = MAP_ROW;
				break;
			}
		}
	}
	//플레이어가 움직일 수 없는 범위 오른쪽 하단 측정
	for (int row = MAP_ROW - 1; row > 0; row--)
	{
		for (int col = MAP_COL - 1; col > 0; col--)
		{
			if (map[row][col] == '*')
			{
				dontMovePos[1].SetX(col);
				dontMovePos[1].SetY(row);
				row = 0;
				break;
			}
		}
	}
}

Pos* MapManager::GetDontMovePos()
{
	return dontMovePos;
}

void MapManager::SetDropItem()
{
	if (Monster::itemPosition->size() <= 0)		//아이템이 있을때만 실행
		return;

	//범위 for문안되가지고 일단 이렇게만듦 나중에 천천히 해보기
	for (auto itemPositionIterator = Monster::itemPosition->begin(); itemPositionIterator != Monster::itemPosition->end(); itemPositionIterator++)
	{
		if ((*itemPositionIterator) == player->GetPos())
		{
			if (player->PickUp())
			{
				Monster::itemPosition->erase(itemPositionIterator);
				return;
			}
		}
	}
}

//피격시 플레이어 상태 표현하려고 사용
void MapManager::SetColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}