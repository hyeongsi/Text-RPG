#include "GameManager.h"
#include <Windows.h>
#include "GameStartUI.h"
#include "SelectDungeonUI.h"

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

const enum select {
	EXIT = -1,
	NEWGAME,
	CHARACTERSELECET,
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
	{
		gameManager.Play(menuSelect);
	}
	else if (menuSelect == CHARACTERSELECET)
	{
		return 0;		//여기에는 이전 캐릭터 선택하는 UI만들어서 넣기, 반환값 saveCharacterNumber넣고
		// gameManager.Play(saveCharacterNumber);
	}	

	//던전선택 UI만들기
	SelectDungeonUI* selectDungeonUI = new SelectDungeonUI();

	while (1) {
		system("cls");
		dungeonSelect = selectDungeonUI->Select();
		dungeonSelect = gameManager.StartDungeon(dungeonSelect);


		if (EXIT == dungeonSelect)
		{
			//플레이어에서 할당받은거 있으면 여기서 삭제해야됨
			break;
		}
	}

	//게임종료시 map할당받은 반환
	delete selectDungeonUI;

	return 0;
}
