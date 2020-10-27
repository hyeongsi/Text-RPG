#pragma once
#include "UI.h"
#include "GameInfo.h"	//캐릭터형태 불러오기
#include "Inventory.h"	//아이템 보유현황 불러오기

class SelectDungeonUI : public UI
{
	map <string, string> select;
	map <string, string> playerTemplate;
	map <string, string> inventory;
	string playerExplanation;
	string inventoryExplanation;
	GameInfo* gameInfo = GameInfo::GetInstance();
	int currentChoice = 3;
	const int DUNGEON1 = 3;
	const int DUNGEON2 = 5;
	const int DUNGEON3 = 7;

public:
	SelectDungeonUI();
	void Show();
	int Select();

	~SelectDungeonUI();
};


