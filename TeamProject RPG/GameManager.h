#pragma once
#include "MapManager.h"
#include "EscMenuUI.h"

class GameManager
{
private:
	MapManager mapManager;
	DelayManager delayManager;
	EscMenuUI escMenuUI;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player = Player::GetInstance();
	vector<Slime*>* slime = Slime::GetInstance();
	vector<Oak*>* oak = Oak::GetInstance();
	vector<Tank*>* tank = Tank::GetInstance();

	bool isOpenInventory = false;
	string playerName;
	string path = "playerList\\";
public:
	void Play(int saveFileNumber); //게임 시작버튼 눌렀을 때
	int StartDungeon(int dungeonNumber);
	void SavePlayerData();

	void CheckContact();
};

