#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "Player.h"
#include "Slime.h"
#include "GameInfo.h"

constexpr auto MAP_ROW = 30;
constexpr auto MAP_COL = 120;

using namespace std;

class MapManager
{
private:
	char map[MAP_ROW][MAP_COL] = {' '};			//진짜 맵 정보
	char tempMap[MAP_ROW][MAP_COL] = {' '};		//출력할 맵 정보

	ifstream fcin;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player;
	vector<Slime*>* slime;

	//플레이어가 움직일 수 있는 범위의 좌표 저장
	Pos dontMovePos[2];  //0:leftUpPos,   1:RightDownPos

public:
	void GoToXY(SHORT x, SHORT y);
	void LoadMap(int num);

	void PrintMap();
	void PrintCharacter(Character* character);
	void PrintWeapon(string weapon);
	void PrintSlime(vector<Slime*>* slime);

	void LoadCanMovePos();
	Pos* GetDontMovePos();
};

