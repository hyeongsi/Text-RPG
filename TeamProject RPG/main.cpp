#include "GameManager.h"
#include "MapManager.h"
#include <Windows.h>

#include "Player.h"

#include <iostream>
int main()
{
	GameManager gameManager;
	MapManager mapManager;
	Player* player = new Player();

	mapManager.PrintCharacter(player);

	system(" mode  con lines=30   cols=120 ");
}