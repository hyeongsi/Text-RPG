#pragma once
#include "Character.h"
#include "Inventory.h"
#include <time.h>
#include <Windows.h>

const enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player : public Character
{
private:
	static Player* playerInstance;
	Player() {};
	Inventory inventory;
	
	string holdWeapon = "sword";

	int walkCount = 0;
	bool isWalking = false;
	bool isAttack = false;
	bool isPickup = false;
	bool isSurvival = true;
	int dir = RIGHT;
	bool dontMoveDir[4] = { false };	//0: 상, 1:하, 2:좌, 3:우

public:
	static Player* GetInstance();
	static void ReleaseInstance();

	void Init();
	void SetStats(const int hpNum, const int powerNum);

	void CheckDontMoveDir(Pos leftUp, Pos rightDown);

	const int InputBehavior();	//행동 입력받는 함수
	const int Move(const int direct4);	//이동 함수
	const int Attack();	//공격 함수
	const int SetPickUpState();//습득 상태 설정

	const bool PickUp();	//아이템 습득 시 인벤토리에 저장
	void OpenInventory();		//인벤토리 열기
	void CloseInventory();		//인벤토리 닫기
	const int GetInventoryItem(int itemIndex);

	void Die();		//죽는 함수

	const string GetHoldWeapon();	//가지고 있는 무기 이름 리턴

	const int GetIsWalking();		//움직임 유무 리턴
	const int GetIsAttacking();		//공격 유무 리턴
	const int GetIsPickUp();		//줍기상태 유무 리턴
	const bool GetWalkCount();		//walkCount로 걷는모션 구현 위해 리턴
	const int GetDir();			//보고있는 방향 리턴
};

enum Behavior
{
	NONE,
	MOVE,
	ATTACK,
	PICKUP
};


