#pragma once
#include "Character.h"
#include <Windows.h>

class Player : public Character
{
private:
	static Player* playerInstance;
	Player() {};

	int walkCount = 0;
	bool isWalking = false;
	bool dir = false; //false : 오른쪽,   true : 왼쪽
public:
	static Player* GetInstance();
	static void ReleaseInstance();

	void SetStats(int hpNum, int powerNum);

	void Move();	//이동 함수
	void Die();		//죽는 함수

	const int GetIsWalking();		//움직임 유무 리턴
	const bool GetWalkCount();		//walkCount로 걷는모션 구현 위해 리턴
	const bool GetDir();			//보고있는 방향 리턴
};

