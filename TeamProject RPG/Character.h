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

	const Pos& GetPos();
	void SetPos(const int& x, const int& y);

	int GetPower() const;		//서로 타격당할때 공격력받아오기위해 추가
	int GetHp() const;

	void SetHp(int hp);
	void SetPower(int power);
	void SetMaxHp(int Hp);
};

const enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};