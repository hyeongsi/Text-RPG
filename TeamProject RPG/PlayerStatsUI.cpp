#include "PlayerStatsUI.h"

void PlayerStatsUI::PrintHp(const int& hp) const
{
	GoToXY(50, 31);
	cout << "                        ";
	GoToXY(50, 31);
	cout << "HP : " << hp << endl;
}

void PlayerStatsUI::PrintMp(const int& mp) const
{
	GoToXY(50, 32);
	cout << "                        ";
	GoToXY(50, 32);
	cout << "MP : " << mp << endl;
}

void PlayerStatsUI::PrintExp(const int& exp) const
{
	GoToXY(50, 33);
	cout << "                        ";
	GoToXY(50, 33);
	cout << "exp : " << exp << " / 100"<< endl;
}

void PlayerStatsUI::PrintLevel(const int& level) const
{
	GoToXY(50, 35);
	cout << "Level : " << level << endl;
}
