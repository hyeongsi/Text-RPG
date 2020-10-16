#pragma once
#include "MapManager.h"
#include "GameInfo.h"
#include "Player.h"

class GameManager
{
private:
	MapManager* map;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player = new Player;

public:
	void Play(int saveFileNumber); //게임 시작버튼 눌렀을 때
	void StartDungeon(int dungeonNumber);

	void CheckContact();
};

