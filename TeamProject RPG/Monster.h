#pragma once
#include "Character.h"
#include <vector>

class Monster : public Character
{	
protected:
	static vector<Monster*>* monster;
	DelayManager moveDelaymanager;
	DelayManager attackDelaymanager;
	bool isMove = true;		//정해진시간에 움직이기위해 사용할 변수,, 각 슬라임들마다 움직임을 판단해야해서 객체마다 가지고있어야해서 여기다선언
	bool isAttacked = false;	//맞았는지여부
	bool isInvincibility = false;	//무적상태여부
	int invincibilityTime = 0;	//무적시간
	int bounceSize = 0;		//맞았을때 튕겨나갈크기
	int speed = 0;		//기본값지정 값은 파일에서 읽어서 저장함

public:
	static void AddInstance();
	static void ReleaseInstance();
	static vector<Monster*>* GetInstance();
	static Pos* itemPosition;	//아이템박스의 좌표(죽은몬스터의 좌표)

	void MonsterSetStats(const int& hp, const int& power, const int& speed);
	void Setting(const int& invincibilityTime, const int& bounceSize);
	void Die();		//죽는 함수

	virtual void SetStats(int hp, int power, int speed, int exp, int itemDropPercentage) = 0;
	virtual void Move(const int& playerXPosition, const int& playerYPosition) = 0;
	virtual void IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower) = 0;
};

