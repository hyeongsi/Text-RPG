#pragma once
#include "Character.h"
#include "Inventory.h"
#include "PlayerStatsUI.h"
#include <time.h>
#include <Windows.h>

class Skill;
class Player : public Character
{
private:
	static Player* playerInstance;
	Player() {};
	Inventory inventory;
	PlayerStatsUI playerStatsUI;
	
	string holdWeapon = "sword";

	int walkCount = 0;
	bool isWalking = false;
	bool isAttack = false;
	bool isPickup = false;
	bool isSurvival = true;
	bool isActivePowerBuff = false;	//버프 적용 유무

	int exp = 0;	//경험치   /  100되면 level +1
	int level = 1;	//레벨

	int dir = RIGHT;
	bool dontMoveDir[4] = { false };	//0: 상, 1:하, 2:좌, 3:우

	//피격당했을때 잠깐무적을 위해 추가
	DelayManager hitDelaymanager;
	bool isInvincibility = false;	//무적상태여부
	const int INVINCIBILITY_TIME = 2500;	//무적시간
	const int NUCKBACK_SIZE = 10;		//맞았을때 밀려날 크기

	//버프 지속시간 및 이펙트
	DelayManager buffDelaymanager;
public:
	static Player* GetInstance();
	static void ReleaseInstance();

	void Init();
	void SetStats(const int& hpNum, const int& powerNum, const int& exp = 0, const int& level = 0, const string& weapon = "sword");
	void SyncStatsUI();

	void CheckDontMoveDir(Pos leftUp, Pos rightDown);

	const int InputBehavior();	//행동 입력받는 함수
	const int Move(const int direct4);	//이동 함수
	const int Attack();	//공격 함수
	const int SetPickUpState();//습득 상태 설정

	const bool PickUp(const int& itemNumber = -1);	//아이템 습득 시 인벤토리에 저장
	void UseItem(int itemNumber);	//아이템 사용
	void OpenInventory();		//인벤토리 열기
	void CloseInventory();		//인벤토리 닫기
	const int GetInventoryItem(int itemIndex);

	void UseSkill(Skill * skill);

	void Die();		//죽는 함수

	const string GetHoldWeapon();	//가지고 있는 무기 이름 리턴

	const int GetIsWalking();		//움직임 유무 리턴
	const int GetIsAttacking();		//공격 유무 리턴
	const int GetIsPickUp();		//줍기상태 유무 리턴
	const bool GetWalkCount();		//walkCount로 걷는모션 구현 위해 리턴
	const int GetDir();			//보고있는 방향 리턴
	const int GetLevel();
	const int GetExp();
	const string& GetCurrentWeapon();
	Inventory& GetInventory();
	void SetExp(const int exp);	//경험치 증가

	void IsHit(const Pos& monsterPosition, const Pos& leftLimit, const Pos& rightLimit, int monsterPower);
	void IsInvincibilityTimer();
	bool GetIsInvincibility();

	void IsActiveBuffTimer();
	void SetBuffTime(const int time);
	const bool& IsActivePowerBuff();
};

enum Behavior
{
	NONE,
	MOVE,
	ATTACK,
	PICKUP,
	SKILL1,
	SKILL2,
	SKILL3
};





