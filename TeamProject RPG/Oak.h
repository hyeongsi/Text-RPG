#pragma once
#include <vector>
#include "Character.h"
#include "Player.h"
#include "DelayManager.h"

class Oak : public Character
{
private:
	Player* player = Player::GetInstance();
	static vector<Oak*>* oak;
	DelayManager moveDelaymanager;
	DelayManager attackDelaymanager;
	bool isMove = true;			//정해진시간에 움직이기위해 사용할 변수
	int speed = 1000;
	Oak() {};

	//무기에맞았다면
	bool isAttacked = false;
	bool isInvincibility = false;	//무적상태여부
	int invincibilityTime = 100;	//무적시간
	int rename = 5;		//맞았을때 밀려날 크기? 이름다시짓기



public:
	static void AddInstance();
	static vector<Oak*>* GetInstance();
	static void ReleaseInstance();

	//아이템박스의 좌표(죽은슬라임의 좌표)
	static Pos* itemPosition;

	void SetStats(int hp, int power, int speed);

	void Move();	//이동 함수
	void Die();		//죽는 함수
	void isHit(int playerXPosition, int playerYPosition);	//맞으면실행
};

