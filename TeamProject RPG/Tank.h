#pragma once
#include "Monster.h"

class Tank : public Monster
{
public:
	static void AddInstance();

	static Pos* itemPosition;	//아이템박스의 좌표(죽은탱크의 좌표).. 아이템박스좌표삭제만들기
	static int exp;
	static int itemDropPercentage;

	virtual void SetStats(int hp, int power, int speed, int exp, int itemDropPercentage);	//스텟설정
	virtual void Move(const int& playerXPosition, const int& playerYPosition);	//이동 함수
	virtual void IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower, const bool isAttack=false);	//맞으면실행

};



