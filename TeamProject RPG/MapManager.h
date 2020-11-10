#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <ctime>
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
	vector<Monster*>* monster = nullptr;
	Pos exitPosition;		//탈출구 좌표

	//아이템드랍관련변수들
	int monsterNumber= 0;		//몬스터들의 수가 들어갈 변수.. 아이템드랍조건에 사용
	int isMonsterItemDrop = -1;	//아이템드랍여부를판단할변수 itemDrop == ITEM_DROP이면 아이템박스떨구기
	int getItemNumber = 0;		//획득한 아이템수
	list<Pos> itemPosition;

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

	void LoadCanMovePos();
	Pos* GetDontMovePos();
	void SetDropItem();

	void SetColor(int forground, int background);
};

