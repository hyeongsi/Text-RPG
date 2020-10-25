#include "GameManager.h"

void GameManager::Play(int saveFileNumber)
{
	gameInfo->LoadSaveData(saveFileNumber); // 세이브파일 번호
	gameInfo->LoadPlayerShape(saveFileNumber);
	gameInfo->LoadWeaponData();
}

void GameManager::StartDungeon(int dungeonNumber)
{
	bool loop = true;
	Pos *dontMovePos;
	int tempPlayerState;

	map = new MapManager();
	map->LoadMap(dungeonNumber);
	dontMovePos = map->GetDontMovePos();	//이동불가 영역 받아서 사용

	slime = Slime::GetInstance();
	if (slime != nullptr)		//슬라임객체가 존재하면 슬라임형태 불러오기 + 슬라임에 스텟설정하기
	{
		gameInfo->LoadSlimeShape();
		gameInfo->LoadSlimeStats();
	}
	//다른몬스터도 추가되면 넣기

	map->PrintMap();
	while (loop)
	{
		if (delayManager.CheckEndDelay())
		{
			player->CheckDontMoveDir(dontMovePos[0], dontMovePos[1]);
			tempPlayerState = player->InputBehavior();

			if (slime != nullptr)
			{
				for (int i = 0; i < slime->size(); i++)
					(*slime)[i]->Move();		//움직임	
			}

			CheckContact();		//플레이어와 몬스터 피격 유무 확인

			//플레이어 상태를 기준으로 행동 실행
			switch (tempPlayerState)
			{
			case ATTACK:
				//slime->Ishit(player->GetPos().GetX(), player->GetPos().GetY())
				//player pos를 기준으로  y+-1 범위에 슬라임 있으면 hit() 실행

				if (slime != nullptr)
				{
					for (int i = 0; i < slime->size(); i++)
						(*slime)[i]->isHit(player->GetPos().GetX(), player->GetPos().GetY());		//피격여부
				}
				break;
			case PICKUP:

				break;
			}

			map->PrintMap();
		}
	}


}

void GameManager::CheckContact()
{
	//피격 시
	//player->Hit(slime->Getpower());
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();
	bool isCrash = false;

	if (slime != nullptr)
	{
		int slimeXPosition;
		int slimeYPosition;
		for (int i = 0; i < slime->size(); i++)
		{
			slimeXPosition = (*slime)[i]->GetPos().GetX();
			slimeYPosition = (*slime)[i]->GetPos().GetY();

			for (int y = -2; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					//여기 이론상계산해보니까 4중첩for문인것같은데..
				}
			}
		}
	}

	if (isCrash)
		player->Hit((*slime)[0]->GetPower());
}

