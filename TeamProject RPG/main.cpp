#include "GameManager.h"
#include <Windows.h>

void SetConsole()
{
	system("title DUNGEON-RPG게임");
	system("mode con:cols=120 lines=120");

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int main()
{
	SetConsole();

	GameManager gameManager;
	if (EXIT == gameManager.TitleMenuPrint())
		return 0;

	int returnValue = 0;
	while (true)
	{
		returnValue = gameManager.SelectDungeonMenuPrint();
		if (EXIT != returnValue)
			returnValue = gameManager.StartDungeon(returnValue);
		
		if (EXIT == returnValue)
		{
			Player::ReleaseInstance();
			Npc::ReleaseInstance();
			MapManager::ReleaseInstance();
			return 0;
		}

	}
}
