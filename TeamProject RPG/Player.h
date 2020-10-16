#pragma once
#include "Character.h"

class Player : public Character
{
private:

public:
	void Move();	//이동 함수
	void Die();		//죽는 함수
};

