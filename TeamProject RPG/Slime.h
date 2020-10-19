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
	DelayManager delaymanager;
	bool isMove = true;			//정해진시간에 움직이기위해 사용할 변수
	int speed = 1000;
	Slime() {};

public:
	static void AddInstance();
	static vector<Slime*>* GetInstance();
	static void ReleaseInstance();

	void SetStats(int hp, int power, int speed);

	void Move(int index);	//이동 함수
	void Move();	//이동 함수.. 가상함수라 어쩔수없이
	void Die();		//죽는 함수

};

