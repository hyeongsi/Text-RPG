#pragma once
#include "Character.h"

class Player : public Character
{
private:

public:
	void SetStats(int hpNum, int powerNum);

	void Move();	//이동 함수
	void Die();		//죽는 함수


};

