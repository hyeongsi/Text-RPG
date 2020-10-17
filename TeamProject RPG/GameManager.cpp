#include "GameManager.h"

void GameManager::Play(int saveFileNumber)
{
	gameInfo->LoadSaveData(saveFileNumber); // 세이브파일 번호
	gameInfo->LoadPlayerShape(saveFileNumber);
}

void GameManager::StartDungeon(int dungeonNumber)
{
	bool loop = true;

	map = new MapManager();
	map->LoadMap(dungeonNumber);

	while (loop)
	{
		if (delayManager.CheckEndDelay())
		{
			map->PrintMap();
			player->Move();
		}
		
	}

}

void GameManager::CheckContact()
{

}

