#pragma once
#include "Pos.h"
#include "DelayManager.h"

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

//이거 monster에도 필요한데 player를 include안시킬거라 character로 옮겨서
//모든 캐릭터라 사용할 수 있게 했음
const enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};