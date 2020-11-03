#include "GameManager.h"

void GameManager::Play(int saveFileNumber)
{
	if (0 == saveFileNumber)
	{
		system("cls");
		mapManager.GoToXY(30, 10);
		cout << "닉네임을 입력하세요 : ";
		cin >> playerName;
		path += playerName + ".ini";
	}
	gameInfo->LoadSaveData(saveFileNumber); // 세이브파일 번호
	gameInfo->LoadPlayerShape(saveFileNumber);
	gameInfo->LoadWeaponData();
}

int GameManager::StartDungeon(int dungeonNumber)
{
	if (0 == dungeonNumber)
		return -1;

	bool loop = true;
	Pos *dontMovePos;
	int tempPlayerState;
	int escUIState = NOTHING;

	mapManager.Init();
	mapManager.LoadMap(dungeonNumber);
	dontMovePos = mapManager.GetDontMovePos();	//이동불가 영역 받아서 사용
	gameInfo->LoadItemBoxShape();		//던전들어가면 아이템박스형태 읽기

	slime = Slime::GetInstance();
	if (slime != nullptr)		//슬라임객체가 존재하면 슬라임형태 불러오기 + 슬라임에 스텟설정하기
	{
		gameInfo->LoadSlimeShape();
		gameInfo->LoadSlimeStats();
	}
	oak = Oak::GetInstance();
	if (oak != nullptr)		//오크객체가 존재하면 오크형태 불러오기 + 오크에 스텟설정하기
	{
		gameInfo->LoadOakShape();
		gameInfo->LoadOakStats();
	}
	tank = Tank::GetInstance();
	if (tank != nullptr)		//탱크객체가 존재하면 탱크형태 불러오기 + 탱크에 스텟설정하기
	{
		gameInfo->LoadTankShape();
		gameInfo->LoadTankStats();
	}

	mapManager.PrintMap(isOpenInventory);
	player->Init();
	while (loop)
	{
		escUIState = NOTHING;
		if (delayManager.CheckEndDelay())
		{
			player->CheckDontMoveDir(dontMovePos[0], dontMovePos[1]);
			tempPlayerState = player->InputBehavior();

			if (slime != nullptr)
			{
				for (int i = 0; i < slime->size(); i++)
					(*slime)[i]->Move();		//움직임	
			}
			if (oak != nullptr)
			{
				for (int i = 0; i < oak->size(); i++)
					(*oak)[i]->Move();		//움직임	
			}
			if (tank != nullptr)
			{
				for (int i = 0; i < tank->size(); i++)
					(*tank)[i]->Move();		//움직임	
			}

			CheckContact();		//플레이어와 몬스터 피격 유무 확인

			//플레이어 상태를 기준으로 행동 실행
			switch (tempPlayerState)
			{
			case ATTACK:
				if (slime != nullptr)
				{
					for (int i = 0; i < slime->size(); i++)
						(*slime)[i]->IsHit(player->GetPos().GetX(), player->GetPos().GetY());	//피격여부
				}
				if (oak != nullptr)
				{
					for (int i = 0; i < oak->size(); i++)
						(*oak)[i]->isHit(player->GetPos().GetX(), player->GetPos().GetY());		//피격여부
				}
				if (tank != nullptr)
				{
					for (int i = 0; i < tank->size(); i++)
						(*tank)[i]->isHit(player->GetPos().GetX(), player->GetPos().GetY());	//피격여부
				}
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

		
		
		//몬스터숫자세기
		size_t monsterNumber = 0;
		if (slime != nullptr)
			monsterNumber += slime->size();
		if (oak != nullptr)
			monsterNumber += oak->size();
		if (tank != nullptr)
			monsterNumber += tank->size();

		//몬스터가 다죽으면 던전선택화면으로이동
		//여기 문제는 아이템줍지도못하고 강제탈출됨 던전탈출조건 추가필요
		if (monsterNumber <= 0 || player->GetHp() <= 0 || escUIState == EXIT_ESC_MENU)
		{
			loop = false;
			player->Init();

			Slime::ReleaseInstance();
			Oak::ReleaseInstance();
			Tank::ReleaseInstance();
		}
 	}

	SavePlayerData();	//던전하나깰때마다 정보저장

	return 0;
}

void GameManager::SavePlayerData()
{
	//여기서 플레이어 정보 기록하기 던전에서 탈출했을때
	//게임시작할 때 이름 입력받아서 playerName에 넣기
	string playerHp = to_string(player->GetHp());			//체력
	string playerPower = to_string(player->GetPower());		//공격력
	string playerLevel = to_string(player->GetLevel());		//레벨
	string playerExp = to_string(player->GetExp());			//경험치

	gameInfo->WriteData(playerName, "hp", playerHp, path);
	gameInfo->WriteData(playerName, "power", playerPower, path);
	gameInfo->WriteData(playerName, "level", playerLevel, path);
	gameInfo->WriteData(playerName, "exp", playerExp, path);
}

//플레이어와 적의 충돌처리
//일단 만들긴했는데  간단한방법이 있을것같은데 더복잡하게 만든느낌
void GameManager::CheckContact()
{
	//피격 시
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();
	bool isCrashSilme = false;
	bool isCrashOak = false;
	bool isCrashTank = false;

	//충돌했을때 몬스터의 인덱스값을 저장할 변수
	int crashIndex = -1;

	if (slime != nullptr)
	{
		int slimeXPosition;
		int slimeYPosition;
		for (int i = 0; i < slime->size(); i++)
		{
			slimeXPosition = (*slime)[i]->GetPos().GetX();
			slimeYPosition = (*slime)[i]->GetPos().GetY();

			for (int x = -1; x <= 1; x++)
			{
				for (int xx = -1; xx <= 1; xx++)
				{
					//플레이어위쪽 슬라임위쪽 검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition) == (playerYPosition))
					{
						isCrashSilme = true;
						crashIndex = i;
					}

					//플레이어위쪽 슬라임아래쪽 검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition) == (playerYPosition - 2))
					{
						isCrashSilme = true;
						crashIndex = i;
					}

					//플레이어아래쪽 슬라임위쪽 검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition - 2) == (playerYPosition))
					{
						isCrashSilme = true;
						crashIndex = i;
					}

					//플레이어아래쪽 슬라임아래쪽 검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition - 2) == (playerYPosition - 2))
					{
						isCrashSilme = true;
						crashIndex = i;
					}

					//플레이어 위쪽 슬라임중간검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition - 1) == (playerYPosition - 2))
					{
						isCrashSilme = true;
						crashIndex = i;
					}

					//플레이어 아래쪽 슬라임중간검사
					if ((slimeXPosition + xx) == (playerXPosition + x) && (slimeYPosition - 1) == (playerYPosition))
					{
						isCrashSilme = true;
						crashIndex = i;
					}
				}
			}
		}
	}

	if (oak != nullptr && isCrashSilme == false)
	{
		int oakXPosition;
		int oakYPosition;
		for (int i = 0; i < oak->size(); i++)
		{
			oakXPosition = (*oak)[i]->GetPos().GetX();
			oakYPosition = (*oak)[i]->GetPos().GetY();

			for (int x = -1; x <= 1; x++)
			{
				for (int xx = -1; xx <= 1; xx++)
				{
					//플레이어위쪽 오크위쪽 검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition) == (playerYPosition))
					{
						isCrashOak = true;
						crashIndex = i;
					}

					//플레이어위쪽 오크아래쪽 검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition) == (playerYPosition - 2))
					{
						isCrashOak = true;
						crashIndex = i;
					}

					//플레이어아래쪽 오크위쪽 검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition - 2) == (playerYPosition))
					{
						isCrashOak = true;
						crashIndex = i;
					}

					//플레이어아래쪽 오크아래쪽 검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition - 2) == (playerYPosition - 2))
					{
						isCrashOak = true;
						crashIndex = i;
					}

					//플레이어 위쪽 오크중간검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition - 1) == (playerYPosition - 2))
					{
						isCrashOak = true;
						crashIndex = i;
					}

					//플레이어 아래쪽 오크중간검사
					if ((oakXPosition + xx) == (playerXPosition + x) && (oakYPosition - 1) == (playerYPosition))
					{
						isCrashOak = true;
						crashIndex = i;
					}
				}
			}
		}
	}

	if (tank != nullptr && isCrashOak == false)
	{
		int tankXPosition;
		int tankYPosition;
		
		for (int i = 0; i < tank->size(); i++)
		{
			tankXPosition = (*tank)[i]->GetPos().GetX();
			tankYPosition = (*tank)[i]->GetPos().GetY();

			for (int x = -1; x <= 1; x++)
			{
				for (int xx = -1; xx <= 1; xx++)
				{
					//플레이어위쪽 탱크위쪽 검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition) == (playerYPosition))
					{
						isCrashTank = true;
						crashIndex = i;
					}

					//플레이어위쪽 탱크아래쪽 검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition) == (playerYPosition - 2))
					{
						isCrashTank = true;
						crashIndex = i;
					}

					//플레이어아래쪽 탱크위쪽 검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition - 2) == (playerYPosition))
					{
						isCrashTank = true;
						crashIndex = i;
					}

					//플레이어아래쪽 탱크아래쪽 검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition - 2) == (playerYPosition - 2))
					{
						isCrashTank = true;
						crashIndex = i;
					}

					//플레이어 위쪽 탱크중간검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition - 1) == (playerYPosition - 2))
					{
						isCrashTank = true;
						crashIndex = i;
					}

					//플레이어 아래쪽 탱크중간검사
					if ((tankXPosition + xx) == (playerXPosition + x) && (tankYPosition - 1) == (playerYPosition))
					{
						isCrashTank = true;
						crashIndex = i;
					}
				}
			}
		}
	}

	if (isCrashSilme == true)
		player->IsHit((*slime)[crashIndex]->GetPos(), mapManager.GetDontMovePos()[0], mapManager.GetDontMovePos()[1], (*slime)[crashIndex]->GetPower());
	else if (isCrashOak == true)
		player->IsHit((*oak)[crashIndex]->GetPos(), mapManager.GetDontMovePos()[0], mapManager.GetDontMovePos()[1], (*slime)[crashIndex]->GetPower());
	else if (isCrashTank == true)
		player->IsHit((*tank)[crashIndex]->GetPos(), mapManager.GetDontMovePos()[0], mapManager.GetDontMovePos()[1], (*slime)[crashIndex]->GetPower());
}