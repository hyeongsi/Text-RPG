#include "GameManager.h"

void GameManager::Play(int saveFileNumber)
{
	switch (saveFileNumber)
	{
	case 1:
		gameInfo->LoadSaveData(1); // 세이브파일 번호
		break;
	case 2:
		gameInfo->LoadSaveData(2); // 세이브파일 번호
		break;
	default:
		gameInfo->LoadSaveData(-1); // 세이브파일 번호
		break; //새게임
	}
}

void GameManager::StartDungeon(int dungeonNumber)
{
	bool loop = true;

	map = new MapManager(player);
	map->LoadMap(dungeonNumber);

	while (loop)
	{
		map->PrintMap();
		player->Move();
	}

}

void GameManager::CheckContact()
{

}

