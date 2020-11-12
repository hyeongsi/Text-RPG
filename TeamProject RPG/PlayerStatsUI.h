#pragma once
#include "UI.h"
class PlayerStatsUI :public UI
{
private:

public:
	void PrintHp(const int& hp) const;			//hp출력
	void PrintMp(const int& mp) const;			//mp 출력
	void PrintExp(const int& exp) const;			//보유 경험치 출력
	void PrintLevel(const int& level) const;		//level 출력
};

