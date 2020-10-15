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
	virtual void Move();	//�̵� �Լ�
	virtual void Die();		//�״� �Լ�
	void Hit(const int power);	//�ǰ� �Լ�

	Pos GetPos();
	const string (*GetShape())[ROW];
};

