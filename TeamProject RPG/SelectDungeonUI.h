#pragma once
#include "UI.h"
#include "GameInfo.h"	//캐릭터형태 불러오기
#include "Inventory.h"	//아이템 보유현황 불러오기

class SelectDungeonUI : public UI
{
	map <string, string> select;
	map <string, string> playerTemplate;
	map <string, string> inventory;
	map <string, int> playerStat;
	string playerExplanation;
	string inventoryExplanation;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player = Player::GetInstance();
	int currentChoice = 3;
	const int DUNGEON1 = 3;
	const int DUNGEON2 = 5;
	const int DUNGEON3 = 7;
	const int gameExit = 9;

public:
	void Init();

	SelectDungeonUI();
	void Show();
	int Select();

	//~SelectDungeonUI();
};


