#pragma once
#include <Windows.h>
#include <map>
#include <iostream>
#include "Player.h"
#include "Slime.h"
#include "Tank.h"
#include "Oak.h"

constexpr auto SHAPE_ROW = 10;
constexpr auto SHAPE_COL = 3;

class GameInfo
{
private:
	map<string, string> playerShape;

	map<string, string> slimeShape;
	map<string, string> oakShape;
	map<string, string> tankShape;

	map<string, string> weaponShape;
	map<string, string> weaponSwingShape;
	map<string, string> itemBoxShape;
	Player* player = Player::GetInstance();
	vector<Slime*>* slime = nullptr;
	vector<Oak*>* oak = nullptr;
	vector<Tank*>* tank = nullptr;
	static GameInfo* gameInfoInstance;

	TCHAR loadData[256] = { '\0' };
	GameInfo() {};
public:
	static GameInfo* GetInstance();
	static void ReleaseInstance();

	map<string, string> GetShape(const int character);

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

	void LoadOakStats();
	void LoadOakShape();

	void LoadTankStats();
	void LoadTankShape();

	void WriteData(string tempSection, string tempKey, string tempValue, string tempPath);
};
const enum items{
	WEAPON,
	ITEM,
	WEAPON_SWING_SHAPE

};
const enum characters{
	MYPLAYER,
	SLIME,
	OAK,
	TANK,
	ITEMBOX		//..나중에 옮기기
	//그외에 적들 추가후 GetShape()에 넣기
};

