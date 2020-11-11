#pragma once
#include "Monster.h"

class Oak : public Monster
{
public:
	static void AddInstance();
	static int exp;
	static int itemDropPercentage;

	virtual void SetStats(int hp, int power, int speed, int exp, int itemDropPercentage);
	virtual void Move(const int& playerXPosition, const int& playerYPosition);	//이동 함수
	virtual void IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower, const bool isAttack=false);	//맞으면실행
};

