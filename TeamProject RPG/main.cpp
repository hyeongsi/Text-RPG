#include "GameManager.h"
#include "MapManager.h"
#include <Windows.h>

#include "Player.h"

#include <iostream>
int main()
{
	system(" mode  con lines=30   cols=120 ");
	GameManager gameManager;

	gameManager.Play(-1);
	gameManager.StartDungeon(1);

	while (1);
}