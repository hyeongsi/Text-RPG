#pragma once
#include <Windows.h>
#include <map>
#include <iostream>
#include "Player.h"
#include "Slime.h"

constexpr auto SHAPE_ROW = 10;
constexpr auto SHAPE_COL = 4;

class GameInfo
{
private:
	char playerShape[SHAPE_ROW][SHAPE_COL] = {' '};
	char slimeShape[SHAPE_ROW][SHAPE_COL] = {' '};

	//테스트용
	map<string, string> slimeShape2;

	map<string, string> weapon;
	map<string, string> weaponShape;
	map<string, string> itemBoxShape;
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

	//테스트용
	map<string, string> GetShape1(const int character);

	string GetItemShape(string itemName, int option);	//0 : 무기, 1 : 아이템
	
	const int ReadFileInt(const char* section, const char* key, const char* path);
	void ReadFileString(const char* section, const char* key, const char* path);

	void LoadWeaponData();
	void LoadItemBoxShape();

	void LoadSaveData(int dataNumber);
	void LoadPlayerStats(int dataNumber);
	void LoadPlayerShape(int dataNumber);

	void LoadSlimeStats();
	void LoadSlimeShape();

};
const enum items{
	WEAPON,
	ITEM,
	WEAPON_SWING_SHAPE,
	ITEMBOX
};
const enum characters{
	MYPLAYER,
	SLIME
	//그외에 적들 추가후 GetShape()에 넣기
};

