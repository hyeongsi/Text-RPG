#pragma once
#include "Character.h"
#include <iostream>
#include <vector>
#include <list>
#include <array>

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
	int itemDropPercentage = 0;
	static list<int>* deathMonster;		//죽은몬스터저장.. 경험치올리기위해사용
	static list<Pos>* itemPosition;		//아이템박스의 좌표(죽은몬스터의 좌표).. 아이템박스를위해사용

public:
	static void Init();
	static void AddInstance();
	static void ReleaseInstance();
	static vector<Monster*>* GetInstance();

	void SetStats(int hp, int power, int speed, int itemDropPercentage);
	void Setting(const int& invincibilityTime, const int& bounceSize);
	void Die();		//죽는 함수
	void Move(const Pos& position);
	void IsHit(const Pos& position, const int& playerDirection, const int& playerPower, const bool isAttack = false);
	void EarthquakeSkillHit(const Pos& position, const int& playerPower);

	static list<Pos>* GetItemPosition();
	static int GetDeathMonster();

	//몬스터로 인스턴스로 못만들게하기위해서 선언, 아무역할없음
	inline virtual void NoMakeMonster() = 0;
};

namespace MonsterSpace
{
	enum monsterNumber
	{
		SLIME = 1,
		OAK,
		TANK
	};
}