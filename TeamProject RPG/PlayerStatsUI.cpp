#include "PlayerStatsUI.h"

void PlayerStatsUI::PrintHp(int hp)
{
	GoToXY(50, 31);
	cout << "HP : " << hp << endl;
}

void PlayerStatsUI::PrintExp(int exp)
{
	GoToXY(50, 33);
	cout << "exp : " << exp << " / 100"<< endl;
}

void PlayerStatsUI::PrintLevel(int level)
{
	GoToXY(50, 35);
	cout << "Level : " << level << endl;
}
