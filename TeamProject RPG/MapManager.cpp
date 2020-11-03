#include "MapManager.h"

void MapManager::Init()
{
	monsterNumer = 0;	//몬스터들의 수가 들어갈 변수.. 던전탈출조건으로 사용
	slimeNumber = 0;	//현재 슬라임, 오크, 탱크수
	oakNumber = 0;
	tankNumber = 0;
	isSlimeItemDrop = -1;		//아이템드랍여부를판단할변수 itemDrop == ITEM_DROP이면 아이템박스떨구기
	isOakItemDrop = -1;
	isTankItemDrop = -1;
	getItemNumber = 0;		//획득한 아이템수
	slime = nullptr;
	oak = nullptr;
	tank = nullptr;
	itemPosition.clear();
}

void MapManager::GoToXY(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::LoadMap(int num)
{
	string currentDungeon;
	int y = 0;
	char mapPiece;
	itemPosition.clear();

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
			else if (mapPiece == 's')		//슬라임이 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Slime::AddInstance();
				slime = Slime::GetInstance();
				(*slime)[slimeNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 'o')		//오크가 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Oak::AddInstance();
				oak = Oak::GetInstance();
				(*oak)[oakNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			else if (mapPiece == 't')		//탱크가 있을 때 마다 슬라임객체생성후 벡터에넣고 위치저장
			{
				Tank::AddInstance();
				tank = Tank::GetInstance();
				(*tank)[tankNumber++]->SetPos(x, y);
				mapPiece = ' ';
			}
			map[y][x] = mapPiece;
		}
	}
	//플레이어가 움직일 수 있는 범위 측정
	LoadCanMovePos();

	fcin.close();
}

void MapManager::PrintMap(bool isOpenInventory)
{
	//원본맵을 출력할 맵에 복사 후
	for (int col = 0; col < MAP_ROW; col++)
	{
		for (int row = 0; row < MAP_COL; row++)
			tempMap[col][row] = map[col][row];
	}

	//슬라임의 아이템드랍하면 좌표 아이템리스트에넣기
	if (isSlimeItemDrop == ITEM_DROP) {
		Pos tempItemPos;
		tempItemPos.SetX(Slime::itemPosition->GetX());
		tempItemPos.SetY(Slime::itemPosition->GetY());

		itemPosition.emplace_back(tempItemPos);
		isSlimeItemDrop = -1;
	}
	//오크의 아이템드랍하면 좌표 아이템리스트에넣기
	if (isOakItemDrop == ITEM_DROP) {
		Pos tempItemPos;
		tempItemPos.SetX(Oak::itemPosition->GetX());
		tempItemPos.SetY(Oak::itemPosition->GetY());

		itemPosition.emplace_back(tempItemPos);
		isOakItemDrop = -1;
	}
	//탱크의 아이템드랍하면 좌표 아이템리스트에넣기
	if (isTankItemDrop == ITEM_DROP) {
		Pos tempItemPos;
		tempItemPos.SetX(Tank::itemPosition->GetX());
		tempItemPos.SetY(Tank::itemPosition->GetY());

		itemPosition.emplace_back(tempItemPos);
		isTankItemDrop = -1;
	}
	//아이템박스출력
	for (auto itemPositions : itemPosition)
		PrintItemBox(itemPositions.GetX(), itemPositions.GetY());

	//슬라임출력부
	if (slime != nullptr)
	{
		PrintSlime(slime);
		if (slimeNumber > slime->size())	//슬라임이 한마리 죽으면
		{
			srand((unsigned int)time(NULL));
			if(isSlimeItemDrop != ITEM_DROP)
				//isSlimeItemDrop = rand() % 3;	//드랍확률계산 33%확률로 아이템떨구기
				isSlimeItemDrop = 0;			//드랍확률 100%
			slimeNumber--;

			player->SetExp(20);			//경험치 증가
			player->SyncStatsUI();		//ui와 플레이어 데이터 동기화
		}
	}
	//오크출력부
	if (oak != nullptr)
	{
		PrintOak(oak);
		if (oakNumber > oak->size())	//오크 한마리 죽으면
		{
			srand((unsigned int)time(NULL));
			if (isOakItemDrop != ITEM_DROP)
				//isOakItemDrop = rand() % 5;		//드랍확률계산 20%확률로 아이템떨구기
				isOakItemDrop = 0;
			oakNumber--;

			player->SetExp(40);			//경험치 증가
			player->SyncStatsUI();		//ui와 플레이어 데이터 동기화
		}
	}
	//탱크출력부
	if (tank != nullptr)
	{
		PrintTank(tank);
		if (tankNumber > tank->size())		//탱크 한마리 죽으면
		{
			srand((unsigned int)time(NULL));
			if (isTankItemDrop != ITEM_DROP)
				//isTankItemDrop = rand() % 10;		//드랍확률계산 10%확률로 아이템떨구기
				isTankItemDrop = 0;
			tankNumber--;

			player->SetExp(60);			//경험치 증가
			player->SyncStatsUI();		//ui와 플레이어 데이터 동기화
		}
	}

	PrintCharacter(player);
	PrintWeapon(player->GetHoldWeapon());

	if (isOpenInventory)
	{
		player->OpenInventory();
	}

	//출력할 맵 출력
	GoToXY(0, 0);
	for (int y = 0; y < MAP_ROW; y++)
	{
		for (int x = 0; x < MAP_COL; x++)
			cout << tempMap[y][x];
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

void MapManager::PrintSlime(vector<Slime*>* slime)
{
	auto slimeShape = gameInfo->GetShape(SLIME);
	int slimePosX;
	int slimePosY;

	for (int i = 0; i < slime->size(); i++)
	{
		slimePosX = (*slime)[i]->GetPos().GetX();
		slimePosY = (*slime)[i]->GetPos().GetY();

		//머리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY - 2][slimePosX - 1 + index] = slimeShape["head"][index];

		//몸 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY - 1][slimePosX - 1 + index] = slimeShape["body"][index];

		//다리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[slimePosY][slimePosX - 1 + index] = slimeShape["legs"][index];
	}
}

void MapManager::PrintOak(vector<Oak*>* oak)
{
	auto oakShape = gameInfo->GetShape(OAK);
	int oakPosX;
	int oakPosY;

	for (int i = 0; i < oak->size(); i++)
	{
		oakPosX = (*oak)[i]->GetPos().GetX();
		oakPosY = (*oak)[i]->GetPos().GetY();

		//머리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[oakPosY - 2][oakPosX - 1 + index] = oakShape["head"][index];

		//몸 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[oakPosY - 1][oakPosX - 1 + index] = oakShape["body"][index];

		//다리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[oakPosY][oakPosX - 1 + index] = oakShape["legs"][index];
	}
}

void MapManager::PrintTank(vector<Tank*>* tank)
{
	auto tankShape = gameInfo->GetShape(TANK);
	int tankPosX;
	int tankPosY;

	for (int i = 0; i < tank->size(); i++)
	{
		tankPosX = (*tank)[i]->GetPos().GetX();
		tankPosY = (*tank)[i]->GetPos().GetY();

		//머리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[tankPosY - 2][tankPosX - 1 + index] = tankShape["head"][index];

		//몸 출력
		if (player->GetPos().GetX() - (*tank)[i]->GetPos().GetX() > 0)
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[tankPosY - 1][tankPosX - 1 + index] = tankShape["bodyL"][index];
		}
		else
		{
			for (int index = 0; index < SHAPE_COL; index++)
				tempMap[tankPosY - 1][tankPosX - 1 + index] = tankShape["bodyR"][index];
		}


		//다리 출력
		for (int index = 0; index < SHAPE_COL; index++)
			tempMap[tankPosY][tankPosX - 1 + index] = tankShape["legs"][index];
	}
}

void MapManager::PrintItemBox(int positionX, int positionY)
{
	auto itemBoxShape = gameInfo->GetShape(ITEMBOX);

	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[positionY - 2][positionX - 1 + index] = itemBoxShape["head"][index];


	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[positionY - 1][positionX - 1 + index] = itemBoxShape["body"][index];

	for (int index = 0; index < SHAPE_COL; index++)
		tempMap[positionY][positionX - 1 + index] = itemBoxShape["legs"][index];
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
	if (itemPosition.size() <= 0)		//아이템이 있을때만 실행
		return;

	for (auto itemPositionIterator = itemPosition.begin(); itemPositionIterator != itemPosition.end();)
	{
		if ((*itemPositionIterator) == player->GetPos())
		{
			if (player->PickUp())
				itemPosition.erase(itemPositionIterator);

			return;
		}
		else
			itemPositionIterator++;
	}
}