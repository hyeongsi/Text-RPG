#pragma once
#include <Windows.h>
#include "Player.h"

constexpr auto SHAPE_COL = 3;
constexpr auto SHAPE_ROW = 3;

class GameInfo
{
private:
	char playerShape[3][3] = {' '};
	char oakShape[3][3] = { {'b', 'b', 'b'}, {'b', 'b', 'b'}, {'b', 'b', 'b'} };

	Player* player = Player::GetInstance();
	static GameInfo* gameInfoInstance;

	TCHAR loadData[256];
	GameInfo() {};
public:
	static GameInfo* GetInstance();
	static void ReleaseInstance();

	const char(*GetShape(const int character))[SHAPE_ROW];

	const int ReadFileInt(const char* section, const char* key, const char* path);
	void ReadFileString(const char* section, const char* key, const char* path);

	void LoadSaveData(int dataNumber);
	void LoadPlayerStats(int dataNumber);
	void LoadPlayerShape(int dataNumber);
	/*플레이어 hp, ...... ini 파일에서 여기에 다받아
		그런다음에 게임매니저에서 여기 저장된 파일 불러와서
		초기화를 하는거지

		플레이어 hit gameinfo통해 monster damage를 알수있는거지
		1, player, 2 pig, 3 cat 
		hp -=gameinfo. pig.damage

	맵관련정보들..?*/


};

