#pragma once
#include "Character.h"

class Player : public Character
{
private:
	static Player* playerInstance;
	Player() {};
public:
	static Player* GetInstance();
	static void ReleaseInstance();

	void SetStats(int hpNum, int powerNum);

	void Move();	//이동 함수
	void Die();		//죽는 함수


};

