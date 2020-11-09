#include "GameManager.h"
#include <Windows.h>

void SetConsole()
{
	system(" mode  con lines=40   cols=120 ");
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
			return 0;
	}
}
