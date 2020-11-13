#pragma once
#include "MapManager.h"
#include "EscMenuUI.h"
#include "Npc.h"

class GameStartUI;
class SelectDungeonUI;
class GameManager
{
private:
	GameStartUI* gameStartUI;
	SelectDungeonUI* selectDungeonUI;

	MapManager mapManager;
	DelayManager delayManager;
	EscMenuUI escMenuUI;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player = Player::GetInstance();
	Npc* npc = Npc::GetInstance();
	vector<Monster*>* monster = nullptr;

	Pos playerPos;		//플레이어 좌표
	Pos* dontMovePos = nullptr;	//이동불가 영역
	bool isOpenInventory = false;
	string playerName;
	string path = "playerList\\";

	

public:
	GameManager();
	const int TitleMenuPrint();		//타이틀 선택창
	void NewPlayerMenu();
	void LoadPlayerSelectMenu(); //기존 유저 데이터 선택 메뉴

	const int SelectDungeonMenuPrint();		//던전 선택창
	const int StartDungeon(const int& dungeonNumber);

	void LoadDungeonData(const int& dungeonNumber);		//던전 데이터 로드
	void SavePlayerData();

	void CheckContact();
};

const enum select {
	EXIT = -1,
	NEWGAME,
	CHARACTERSELECET,
	STARTGAME
};
