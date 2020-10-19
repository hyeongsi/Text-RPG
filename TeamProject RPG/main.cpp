#include "GameManager.h"
#include "MapManager.h"
#include <Windows.h>

void SetConsole()
{
	//system(" mode  con lines=30   cols=120 ");
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

	gameManager.Play(-1);
	gameManager.StartDungeon(1);

}
