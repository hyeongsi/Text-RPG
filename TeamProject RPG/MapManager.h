#pragma once

#include <fstream>
#include <string>
#include "Player.h"
#include "Slime.h"
#include "GameInfo.h"

constexpr auto MAP_COL = 30;
constexpr auto MAP_ROW = 120;

using namespace std;

class MapManager
{
private:
	char map[MAP_COL][MAP_ROW] = {' '};			//진짜 맵 정보
	char tempMap[MAP_COL][MAP_ROW] = {' '};		//출력할 맵 정보

	ifstream fcin;
	GameInfo* gameInfo = GameInfo::GetInstance();
	Player* player = Player::GetInstance();
	vector<Slime*>* slime;

	//플레이어가 움직일 수 있는 범위의 좌표 저장
	Pos dontMovePos[2];  //0:leftUpPos,   1:RightDownPos

public:
	void GoToXY(const int x,const int y);
	void LoadMap(int num);

	void PrintMap();
	void PrintCharacter(Character* character);
	void PrintSlime(vector<Slime*>* slime);

	void LoadCanMovePos();
	Pos* GetDontMovePos();
};

