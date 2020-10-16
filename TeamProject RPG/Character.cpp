#include "Character.h"

Character::Character()
{
	Hp = 0;
	power = 0;
	//HP, power  shape ini 파일로 로드
}

void Character::Move()
{
}

void Character::Die()
{
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

const string(*Character::GetShape())[ROW]
{
	return shape;
}
