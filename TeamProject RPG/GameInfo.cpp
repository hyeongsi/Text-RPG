#include "GameInfo.h"

GameInfo* GameInfo::gameInfoInstance = nullptr;

GameInfo* GameInfo::GetInstance()
{
	if (gameInfoInstance != nullptr)
		gameInfoInstance = new GameInfo();
	
	return gameInfoInstance;
}

void GameInfo::ReleaseInstance()
{
	if (gameInfoInstance)
	{
		delete gameInfoInstance;
		gameInfoInstance = nullptr;
	}
}

const char(*GameInfo::GetShape(const int character))[SHAPE_ROW]
{
	if(character == 1)
		return playerShape;
	if (character == 2)
		return oakShape;
}

const int GameInfo::ReadFileInt(const char* section, const char* key, const char* path)
{
	return GetPrivateProfileIntA(section, key, 0, path);
 }

void GameInfo::LoadSaveData(int dataNumber)
{
	switch (dataNumber)
	{
	case 1:
		LoadPlayerStats(dataNumber);
		break;
	case 2:
		LoadPlayerStats(dataNumber);
		break;
	default:
		LoadPlayerStats(dataNumber);
		break;	//새게임
	}
}

void GameInfo::LoadPlayerStats(int dataNumber)
{
	int hp = 0;
	int power = 0;

	switch (dataNumber)
	{
	case 1:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	case 2:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");	//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	default:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");
		break;
	}
}