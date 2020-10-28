#pragma once
#include "Pos.h"
#include <iostream>

using namespace std;

class Character
{
protected:
	int MaxHp;
	int Hp;
	int power;
	Pos pos;
public:
	Character();
	virtual void Die() = 0;		//죽는 함수
	void Hit(const int power);	//피격 함수

	Pos GetPos();
	void SetPos(int x, int y);

	int GetPower();		//서로 타격당할때 공격력받아오기위해 추가
	int GetHp();
};

