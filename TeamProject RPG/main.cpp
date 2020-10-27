#include "GameManager.h"
#include <Windows.h>
#include "GameStartUI.h"
#include "SelectDungeonUI.h"

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

const enum select {
	NEWGAME,
	CHARACTERSELECET,
	EXIT
};

int main()
{
	SetConsole();
	int menuSelect = -1;		//게임시작에서 선택여부를 저장할 변수
	int dungeonSelect = 1;		//던전을 선택할 변수

	GameStartUI* gameStartUI = new GameStartUI();
	menuSelect = gameStartUI->Select();
	delete gameStartUI;
	if (menuSelect == EXIT)	//게임종료
		return 0;

	GameManager gameManager;
	if (menuSelect == NEWGAME)
		gameManager.Play(menuSelect);
	else if (menuSelect == CHARACTERSELECET)
	{
		return 0;		//여기에는 이전 캐릭터 선택하는 UI만들어서 넣기
	}	

	//던전선택 UI만들기
	SelectDungeonUI* selectDungeonUI = new SelectDungeonUI();
	dungeonSelect = selectDungeonUI->Select();

	gameManager.StartDungeon(dungeonSelect);


	//게임종료시 map할당반환
	delete selectDungeonUI;

	return 0;
}
