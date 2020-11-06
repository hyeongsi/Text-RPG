#pragma once
#include "MapManager.h"
#include "EscMenuUI.h"

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
	vector<Slime*>* slime = Slime::GetInstance();
	vector<Oak*>* oak = Oak::GetInstance();
	vector<Tank*>* tank = Tank::GetInstance();

	Pos playerPos;		//플레이어 좌표
	Pos* dontMovePos;	//이동불가 영역
	bool isOpenInventory = false;
	string playerName;
	string path = "playerList\\";
public:
	GameManager();
	const int& TitleMenuPrint();		//타이틀 선택창
	void NewPlayerMenu();

	const int SelectDungeonMenuPrint();		//던전 선택창
	void Play(const int& saveFileNumber); //게임 시작버튼 눌렀을 때
	const int& StartDungeon(const int& dungeonNumber);

	void LoadDungeonData(const int& dungeonNumber);		//던전 데이터 로드
	void SavePlayerData();

	void CheckContact();
};

const enum select {
	EXIT = -1,
	NEWGAME,
	CHARACTERSELECET,
};
