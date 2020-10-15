#pragma once
#include "Pos.h"
#include <iostream>

constexpr auto COL = 3;
constexpr auto ROW = 3;

using namespace std;

class Character
{
private:
	int Hp;
	int power;
	Pos pos;
	string shape[COL][ROW] = {" "}; 

public:
	Character();
	virtual void Move();	//이동 함수
	virtual void Die();		//죽는 함수
	void Hit(const int power);	//피격 함수

	Pos GetPos();
	const string (*GetShape())[ROW];
};

