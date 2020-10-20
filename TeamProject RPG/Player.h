#pragma once
#include "Character.h"
#include <Windows.h>

class Player : public Character
{
private:
	static Player* playerInstance;
	Player() {};

	string holdWeapon = "sword";

	int walkCount = 0;
	bool isWalking = false;
	bool isAttack = false;
	bool isPickup = false;
	bool dir = false; //false : 오른쪽,   true : 왼쪽
	bool dontMoveDir[4] = { false };	//0: 상, 1:하, 2:좌, 3:우

public:
	static Player* GetInstance();
	static void ReleaseInstance();

	void SetStats(const int hpNum, const int powerNum);

	void CheckDontMoveDir(Pos leftUp, Pos rightDown);

	void Move();	//이동 함수
	void Attack();	//공격 함수
	void PickItem();//아이템 습득
	void Die();		//죽는 함수

	const string GetHoldWeapon();	//가지고 있는 무기 이름 리턴

	const int GetIsWalking();		//움직ㅇ임 유무 리턴
	const bool GetWalkCount();		//walkCount로 걷는모션 구현 위해 리턴
	const bool GetDir();			//보고있는 방향 리턴
};

