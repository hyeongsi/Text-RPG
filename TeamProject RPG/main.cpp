#include "GameManager.h"
#include <Windows.h>

void SetConsole()
{
	system("title DUNGEON-RPG게임");
	system("mode con cols=120 lines=200");		//찾아도 이유를 모르겠음 안됨

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
	if (gameManager.TitleMenuPrint() == EXIT)
		return 0;

	int returnValue = 0;
	while (true)
	{
		returnValue = gameManager.SelectDungeonMenuPrint();
		if (returnValue != EXIT)
			returnValue = gameManager.StartDungeon(returnValue);
		
		if (returnValue == EXIT)
		{
			Npc::ReleaseInstance();
			return 0;
		}

	}
}
