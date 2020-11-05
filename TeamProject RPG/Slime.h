#pragma once
#include "Monster.h"

class Slime : public Monster
{
private:
	static vector<Slime*>* slime;
	Slime() {};

public:
	static void AddInstance();
	static vector<Slime*>* GetInstance();
	static void ReleaseInstance();

	//아이템박스의 좌표(죽은슬라임의 좌표)
	static Pos* itemPosition;
	static int exp;

	void SetStats(int hp, int power, int speed, int exp);

	void Move(int playerXPosition, int playerYPosition);	//이동 함수
	void Die();		//죽는 함수
	void IsHit(int playerXPosition, int playerYPosition, int playerDirection, int playerPower);	//맞으면실행
};