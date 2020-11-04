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
	bool isMove = true;		//정해진시간에 움직이기위해 사용할 변수,, 각 슬라임들마다 움직임을 판단해야해서 객체마다 가지고있어야해서 여기다선언
	bool isAttacked = false;	//맞았는지여부
	bool isInvincibility = false;	//무적상태여부
	int invincibilityTime = 0;	//무적시간
	int bounceSize = 0;		//맞았을때 튕겨나갈크기
	int speed = 0;		//기본값지정 값은 파일에서 읽어서 저장함
	Slime() {};

public:
	static void AddInstance();
	static vector<Slime*>* GetInstance();
	static void ReleaseInstance();

	//아이템박스의 좌표(죽은슬라임의 좌표)
	static Pos* itemPosition;

	void SetStats(int hp, int power, int speed);
	void Setting(int invincibilityTime, int bounceSize);

	void Move();	//이동 함수
	void Die();		//죽는 함수
	void IsHit(int playerXPosition, int playerYPosition);	//맞으면실행
};

