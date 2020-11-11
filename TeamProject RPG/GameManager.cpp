#include "GameManager.h"
#include "GameStartUI.h"
#include "SelectDungeonUI.h"

GameManager::GameManager()
{
	dontMovePos = nullptr;
	gameStartUI = new GameStartUI();
	selectDungeonUI = new SelectDungeonUI();
}

const int GameManager::TitleMenuPrint()
{
	int menuSelect = -1;		//게임시작에서 선택여부를 저장할 변수
	int dungeonSelect = 1;		//던전을 선택할 변수

	menuSelect = gameStartUI->Select();

	if (menuSelect == EXIT)	//게임종료
	{
		delete gameStartUI;
		delete selectDungeonUI;
		return EXIT;
	}

	if (menuSelect == NEWGAME)
		NewPlayerMenu();
	else if (menuSelect == CHARACTERSELECET)
		LoadPlayerSelectMenu();

	return STARTGAME;
}

void GameManager::NewPlayerMenu()
{
	system("cls");
	mapManager.GoToXY(30, 10);
	cout << "신규생성 닉네임을 입력하세요 : ";

	cin >> playerName;
	path += playerName + ".ini";

	string fileName(path);
	ifstream fin(fileName.c_str());

	if (fin.fail())
	{
		cout << endl;
		cout << "해당 정보가 없습니다. 해당 이름으로 신규 생성합니다." << endl;
		Sleep(1000);

		gameInfo->LoadNewData();
		gameInfo->LoadPlayerShape();
		gameInfo->LoadWeaponData();
		fin.close();
		return;
	}
	else
	{
		cout << endl << endl << endl << "중복되는 닉네임입니다. 새로운 닉네임을 입력해주세요!" << endl;
		Sleep(1000);
		path = "playerList\\";
		fin.close();
		NewPlayerMenu();
	}
}

void GameManager::LoadPlayerSelectMenu()
{
	system("cls");

	mapManager.GoToXY(30, 10);
	cout << "닉네임을 입력하세요 : ";
	cin >> playerName;
	path += playerName + ".ini";

	string fileName(path);
	ifstream fin(fileName.c_str());

	if (fin.fail())
	{
		cout << endl;
		cout << "해당 정보가 없습니다. 해당 이름으로 신규 생성합니다." << endl;
		Sleep(1000);

		gameInfo->LoadNewData();
		gameInfo->LoadPlayerShape();
		gameInfo->LoadWeaponData();
		fin.close();
		return;
	}
	else
	{
		gameInfo->LoadPlayerStats(path, playerName);
		gameInfo->LoadInventoryItem(path, playerName);
		gameInfo->LoadPlayerShape();
		gameInfo->LoadWeaponData();
		fin.close();
	}
}

const int GameManager::SelectDungeonMenuPrint()
{
	SavePlayerData();
	system("cls");
	int returnValue = 0;
	selectDungeonUI->Show();
	returnValue = selectDungeonUI->Select();

	if (returnValue == 0)
	{
		SavePlayerData();
		delete selectDungeonUI;
		return EXIT;
	}
	else
		return returnValue;
}

const int GameManager::StartDungeon(const int& dungeonNumber)
{
	if (0 == dungeonNumber)
		return -1;

	bool loop = true;
	int tempPlayerState;
	int escUIState = NOTHING;
	int buyItem = Shop::NOTHING;		//구매한 아이템

	player->Init();
	mapManager.Init();

	LoadDungeonData(dungeonNumber);
	mapManager.PrintMap(isOpenInventory);
	while (loop)
	{
		playerPos = player->GetPos();

		escUIState = NOTHING;
		if (delayManager.CheckEndDelay())
		{
			player->CheckDontMoveDir(dontMovePos[0], dontMovePos[1]);
			tempPlayerState = player->InputBehavior();

			for (int i = 0; i < monster->size(); i++)
				(*monster)[i]->Move(playerPos.GetX(), playerPos.GetY());		//움직임	

			CheckContact();		//플레이어와 몬스터 피격 유무 확인
			player->IsInvincibilityTimer();		//플레이어 무적시간측정

			//플레이어 상태를 기준으로 행동 실행
			switch (tempPlayerState)
			{
			case ATTACK:
				//몬스터 피격판정검사
				for (int i = 0; i < monster->size(); i++)
					(*monster)[i]->IsHit(playerPos.GetX(), playerPos.GetY(), player->GetDir(), player->GetPower());

				//NPC피격검사 (상점열기)
				buyItem = npc->OpenShop(playerPos.GetX(), playerPos.GetY(), player->GetDir());

				break;
			case PICKUP:
				mapManager.SetDropItem();
				break;
			}

			if (GetAsyncKeyState(VK_TAB) && 0x8000)	//tab 인벤토리 열기
			{
				if (isOpenInventory)
				{
					isOpenInventory = false;
					player->CloseInventory();
				}
				else
					isOpenInventory = true;
			}

			if (GetAsyncKeyState(VK_ESCAPE) && 0x8000)	//esc escMenu 열기	
				escUIState = escMenuUI.OpenEscMenu();

			if (escUIState != NOTHING)
				player->UseItem(escUIState);

			mapManager.PrintMap(isOpenInventory);
		}

		

		//아이템구매.. (-1은 아무것도 안산거)
		if (Shop::NOTHING != buyItem)
		{
			//인벤토리에 추가 구현해야함
			Inventory& tempInventory = player->GetInventory();
			tempInventory.PushItem(buyItem);

			buyItem = -1;
		}

		//조건에 해당하면 던전탈출
		if (player->GetHp() <= 0 || escUIState == EXIT_ESC_MENU)
		{
			loop = false;
			player->Init();
			Monster::ReleaseInstance();
		}
		if (monster->size() <= 0 && (mapManager.GetExitPosition() == player->GetPos()))
		{
			loop = false;
			player->Init();
			Monster::ReleaseInstance();
		}
 	}

	SavePlayerData();

	return 0;
}

void GameManager::LoadDungeonData(const int& dungeonNumber)
{
	mapManager.LoadMap(dungeonNumber);
	dontMovePos = mapManager.GetDontMovePos();	//이동불가 영역 받아서 사용
	gameInfo->LoadItemBoxShape();		//던전들어가면 아이템박스형태 읽기

	monster = Monster::GetInstance();

	gameInfo->LoadMonsterShape(monster);
	gameInfo->LoadMonsterStats(monster);
	gameInfo->LoadMonsterDefaultSettingValue(monster);
	gameInfo->LoadNPCShape();
}

void GameManager::SavePlayerData()
{
	//여기서 플레이어 정보 기록하기 던전에서 탈출했을때
	//게임시작할 때 이름 입력받아서 playerName에 넣기
	string playerHp = to_string(player->GetHp());			//체력
	string playerPower = to_string(player->GetPower());		//공격력
	string playerLevel = to_string(player->GetLevel());		//레벨
	string playerExp = to_string(player->GetExp());			//경험치
	string playerWeapon = player->GetCurrentWeapon();			//무기

	Inventory& tempInventroy = player->GetInventory();
	string playerInventorySize = to_string(tempInventroy.GetInventorySize());	//인벤토리 사이즈

	gameInfo->WriteData(playerName, "hp", playerHp, path);
	gameInfo->WriteData(playerName, "power", playerPower, path);
	gameInfo->WriteData(playerName, "level", playerLevel, path);
	gameInfo->WriteData(playerName, "exp", playerExp, path);
	gameInfo->WriteData(playerName, "size", playerInventorySize, path);
	gameInfo->WriteData(playerName, "currentWeapon", playerWeapon, path);

	for (int inventoryItemNumber = 0; inventoryItemNumber < tempInventroy.GetInventorySize(); inventoryItemNumber++)
	{
		int itemValue= tempInventroy.GetItem(inventoryItemNumber);
		if (itemValue == -1)
			return;

		gameInfo->WriteData(playerName, to_string(inventoryItemNumber),to_string(itemValue), path);
	}
}

//플레이어와 적의 충돌처리
void GameManager::CheckContact()
{
	//피격 시
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();
	bool isCrashMonster = false;

	//몬스터위치
	int monsterXPosition;
	int monsterYPosition;

	//충돌했을때 몬스터의 인덱스값을 저장할 변수
	int crashIndex = -1;
	int tempIndex = -1;

	for (auto monsterIterator = monster->begin(); monsterIterator != monster->end(); monsterIterator++)
	{
		tempIndex++;
		monsterXPosition = (*monsterIterator)->GetPos().GetX();
		monsterYPosition = (*monsterIterator)->GetPos().GetY();

		for (int x = -1; x <= 1; x++)
		{
			for (int xx = -1; xx <= 1; xx++)
			{
				//플레이어위쪽 몬스터위쪽 검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition) == (playerYPosition))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}

				//플레이어위쪽 몬스터아래쪽 검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition) == (playerYPosition - 2))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}

				//플레이어아래쪽 몬스터위쪽 검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition - 2) == (playerYPosition))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}

				//플레이어아래쪽 몬스터아래쪽 검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition - 2) == (playerYPosition - 2))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}

				//플레이어 위쪽 몬스터중간검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition - 1) == (playerYPosition - 2))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}

				//플레이어 아래쪽 몬스터중간검사
				if ((monsterXPosition + xx) == (playerXPosition + x) && (monsterYPosition - 1) == (playerYPosition))
				{
					isCrashMonster = true;
					crashIndex = tempIndex;
				}
			}
		}
		if (isCrashMonster == true)
			player->IsHit((*monster)[crashIndex]->GetPos(), mapManager.GetDontMovePos()[0], mapManager.GetDontMovePos()[1], (*monster)[crashIndex]->GetPower());
	}
}