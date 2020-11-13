#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include "GameInfo.h"

constexpr auto MAP_ROW = 30;
constexpr auto MAP_COL = 120;
constexpr auto ITEM_DROP = 0;

using namespace std;

class MapManager
{
private:
	char map[MAP_ROW][MAP_COL] = {' '};			//진짜 맵 정보
	char tempMap[MAP_ROW][MAP_COL] = {' '};		//출력할 맵 정보

	ifstream fcin;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player;
	Npc* npc = Npc::GetInstance();
	vector<Monster*>* monster = nullptr;
	Pos exitPosition;		//탈출구 좌표

	int monsterNumber= 0;

	//플레이어가 움직일 수 있는 범위의 좌표 저장
	Pos dontMovePos[2];  //0:leftUpPos,   1:RightDownPos

public:
	void Init();

	void GoToXY(SHORT x, SHORT y);
	void LoadMap(const int& num);
	const Pos& GetExitPosition();

	void PrintMap(bool isOpenInventory);
	void PrintCharacter(Character* character);
	void PrintWeapon(string weapon);
	void PrintMonster(Monster* monster);
	void PrintItemBox();
	void PrintNPC();

	void LoadCanMovePos();
	Pos* GetDontMovePos();
	void SetDropItem();

	void SetColor(int forground, int background);
};

