#include "Monster.h"

void Monster::MonsterSetStats(const int& hp, const int& power, const int& speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

void Monster::Setting(const int& invincibilityTime, const int& bounceSize)
{
	this->invincibilityTime = invincibilityTime;
	this->bounceSize = bounceSize;
}

Monster::~Monster()
{
}