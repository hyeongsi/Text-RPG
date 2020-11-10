#pragma once
#include "Monster.h"

class Slime : public Monster
{
public:
	static void AddInstance();
	static int exp;
	static int itemDropPercentage;

	virtual void SetStats(int hp, int power, int speed, int exp, int itemDropPercentage);
	virtual void Move(const int& playerXPosition, const int& playerYPosition);	//이동 함수
	virtual void IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower);	//맞으면실행
};