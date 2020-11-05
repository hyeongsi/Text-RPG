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
	vector<Slime*>* slime;
	vector<Oak*>* oak;
	vector<Tank*>* tank;

	//아이템드랍관련변수들
	int monsterNumer = 0;	//몬스터들의 수가 들어갈 변수.. 던전탈출조건으로 사용
	int slimeNumber = 0;	//현재 슬라임, 오크, 탱크수
	int oakNumber = 0;
	int tankNumber = 0;
	int isSlimeItemDrop = -1;		//아이템드랍여부를판단할변수 itemDrop == ITEM_DROP이면 아이템박스떨구기
	int isOakItemDrop = -1;
	int isTankItemDrop = -1;
	int getItemNumber = 0;		//획득한 아이템수
	list<Pos> itemPosition;

	//플레이어가 움직일 수 있는 범위의 좌표 저장
	Pos dontMovePos[2];  //0:leftUpPos,   1:RightDownPos

public:
	void Init();

	void GoToXY(SHORT x, SHORT y);
	void LoadMap(int num);

	void PrintMap(bool isOpenInventory);
	void PrintCharacter(Character* character);
	void PrintWeapon(string weapon);
	void PrintSlime(vector<Slime*>* slime);
	void PrintOak(vector<Oak*>* oak);
	void PrintTank(vector<Tank*>* tank);
	void PrintItemBox(int positionX, int positionY);

	void LoadCanMovePos();
	Pos* GetDontMovePos();
	void SetDropItem();
};

