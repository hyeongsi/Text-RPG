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
	Slime() {};
	DelayManager delaymanager;
	bool isMove = true;

public:
	static void AddInstance();
	static vector<Slime*>* GetInstance();
	static void ReleaseInstance();

	void SetStats(int hp, int power);

	void Move();	//이동 함수
	void Die();		//죽는 함수

};

