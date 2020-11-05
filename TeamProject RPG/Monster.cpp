#include "Monster.h"

void Monster::MonsterSetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

void Monster::Setting(int invincibilityTime, int bounceSize)
{
	this->invincibilityTime = invincibilityTime;
	this->bounceSize = bounceSize;
}

Monster::~Monster()
{
}