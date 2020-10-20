#pragma once
#include <Windows.h>
#include <map>
#include <iostream>
#include "Player.h"
#include "Slime.h"

constexpr auto SHAPE_ROW = 7;
constexpr auto SHAPE_COL = 3;

class GameInfo
{
private:
	char playerShape[SHAPE_ROW][SHAPE_COL] = {' '};
	char slimeShape[SHAPE_ROW][SHAPE_COL] = {' '};

	map<string, string> weapon;
	Player* player = Player::GetInstance();
	vector<Slime*>* slime;
	static GameInfo* gameInfoInstance;

	TCHAR loadData[256];
	char tempChar[2];
	GameInfo() {};
public:
	static GameInfo* GetInstance();
	static void ReleaseInstance();

	const char(*GetShape(const int character))[SHAPE_COL];
	string GetItemShape(string itemName, int option);	//0 : 무기, 1 : 아이템
	
	const int ReadFileInt(const char* section, const char* key, const char* path);
	void ReadFileString(const char* section, const char* key, const char* path);

	void LoadWeapon();

	void LoadSaveData(int dataNumber);
	void LoadPlayerStats(int dataNumber);
	void LoadPlayerShape(int dataNumber);

	void LoadSlimeStats();
	void LoadSlimeShape();
	/*플레이어 hp, ...... ini 파일에서 여기에 다받아
		그런다음에 게임매니저에서 여기 저장된 파일 불러와서
		초기화를 하는거지

		플레이어 hit gameinfo통해 monster damage를 알수있는거지
		1, player, 2 pig, 3 cat 
		hp -=gameinfo. pig.damage

	맵관련정보들..?*/


};

enum {
	MYPLAYER,
	SLIME
	//그외에 적들 추가후 GetShape()에 넣기
};

