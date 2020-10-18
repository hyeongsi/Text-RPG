#include "Character.h"

Character::Character()
{
	Hp = 0;
	power = 0;

	pos.SetX(10);
	pos.SetY(10);
	//HP, power  shape ini 파일로 로드
}

void Character::Hit(const int power)
{
	Hp -= power;
	if(Hp<=0)
		Die();
}

Pos Character::GetPos()
{
	return pos;
}


void Character::SetPos(int x, int y)
{
	pos.SetX(x);
	pos.SetY(y);
}

