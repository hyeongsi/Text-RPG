#pragma once
#include "UI.h"

class GameStartUI : public UI
{
private:
	map <string, string> title;
	map <string, string> select;
	int currentChoice = 12;
	const int NEWGAME = 12;
	const int CHARACTERSELECET = 14;
	const int EXIT = 16;

private:
	void Show();

public:
	GameStartUI();
	const int Select();
	~GameStartUI();
};