#pragma once
#include "Monster.h"

class Tank : public Monster
{
public:
	static void AddInstance();

	virtual void SetStats(int hp, int power, int speed);	//스텟설정
	virtual void Move(const int& playerXPosition, const int& playerYPosition);	//이동 함수
	virtual void IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower);	//맞으면실행

};



