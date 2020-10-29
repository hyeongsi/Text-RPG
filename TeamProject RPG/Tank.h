#pragma once
#include <vector>
#include "Character.h"
#include "Player.h"
#include "DelayManager.h"

class Tank : public Character
{
private:
	Player* player = Player::GetInstance();
	static vector<Tank*>* tank;
	DelayManager moveDelaymanager;		//움직일때 사용
	DelayManager attackDelaymanager;	//무적시간을 지정할때 사용
	bool isMove = true;			//정해진시간에 움직이기위해 사용할 변수
	int speed = 1000;		//속도 기본값 어차피 ini파일에서 읽어서 사용
	Tank() {};			//슬라임객체를 마음대로 생성하지못하게하기위함

	//무기에맞았다면
	bool isAttacked = false;
	bool isInvincibility = false;	//무적상태여부
	int invincibilityTime = 100;	//무적시간
	int rename = 4;		//맞았을때 밀려날 크기? 이름다시짓기

public:
	static void AddInstance();
	static vector<Tank*>* GetInstance();
	static void ReleaseInstance();
	static Pos* itemPosition;	//아이템박스의 좌표(죽은탱크의 좌표).. 아이템박스좌표삭제만들기

	void SetStats(int hp, int power, int speed);	//스텟설정
	void Move();	//이동 함수
	void Die();		//죽는 함수
	void isHit(int playerXPosition, int playerYPosition);	//맞으면실행

};



