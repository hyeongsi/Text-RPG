#include "GameInfo.h"

GameInfo* GameInfo::gameInfoInstance = nullptr;

GameInfo* GameInfo::GetInstance()
{
	if (gameInfoInstance == nullptr)
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
	if (character == 1)
		return oakShape;
	else
		return playerShape;
}

const int GameInfo::ReadFileInt(const char* section, const char* key, const char* path)
{
	return GetPrivateProfileIntA(section, key, 0, path);
 }

void GameInfo::ReadFileString(const char* section, const char* key, const char* path)
{
	GetPrivateProfileString(section, key,"", loadData, sizeof(loadData), path);
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
	player->SetStats(hp, power);
}

void GameInfo::LoadPlayerShape(int dataNumber)
{
	for (int col = 0; col < SHAPE_COL; col++)	//플레이어 기본 모습 로드
	{
		switch (col)
		{
		case 0:ReadFileString("player", "head", "GameInfo\\player.ini");	//머리
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 1:ReadFileString("player", "body", "GameInfo\\player.ini");	//몸
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 2:ReadFileString("player", "legs", "GameInfo\\player.ini");	//기본다리
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 3:ReadFileString("player", "walkingRight1", "GameInfo\\player.ini");	//우측이동모션1
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 4:ReadFileString("player", "walkingRight2", "GameInfo\\player.ini");	//우측이동모션2
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 5:ReadFileString("player", "walkingLeft1", "GameInfo\\player.ini");	//좌측이동모션1
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		case 6:ReadFileString("player", "walkingLeft2", "GameInfo\\player.ini");	//좌측이동모션2
			for (int row = 0; row < SHAPE_ROW; row++)
				playerShape[col][row] = loadData[row];
			break;
		}
	}
}
