#pragma once
#include <vector>
#include "Character.h"
#include "Player.h"
#include "DelayManager.h"

class Slime : public Character
{
private:
	Player* player = Player::GetInstance();
	static vector<Slime*>* slime;
	DelayManager moveDelaymanager;
	DelayManager attackDelaymanager;
	bool isMove = true;			//정해진시간에 움직이기위해 사용할 변수
	int speed = 1000;
	Slime() {};

	//무기에맞았다면
	bool isAttacked = false;
	bool isInvincibility = false;	//무적상태여부
	int rename = 3;		//맞았을때 밀려날 크기? 이름다시짓기

public:
	static void AddInstance();
	static vector<Slime*>* GetInstance();
	static void ReleaseInstance();

	void SetStats(int hp, int power, int speed);

	void Move(int index);	//이동 함수
	void Move();	//이동 함수.. 가상함수라 어쩔수없이
	void Die();		//죽는 함수
	void isHit(int index);	//맞으면실행
};

