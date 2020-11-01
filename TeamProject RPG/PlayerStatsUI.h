#pragma once
#include "UI.h"
class PlayerStatsUI :public UI
{
private:

public:
	void PrintHp(int hp);			//hp출력
	void PrintExp(int exp);			//보유 경험치 출력
	void PrintLevel(int level);		//level 출력
};

