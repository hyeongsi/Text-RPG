#pragma once
#include "Monster.h"

class Tank : public Monster
{
private:
	static vector<Tank*>* tank;
	Tank() {};			//슬라임객체를 마음대로 생성하지못하게하기위함

public:
	static void AddInstance();
	static vector<Tank*>* GetInstance();
	static void ReleaseInstance();

	static Pos* itemPosition;	//아이템박스의 좌표(죽은탱크의 좌표).. 아이템박스좌표삭제만들기
	static int exp;

	void SetStats(int hp, int power, int speed, int exp);	//스텟설정

	void Move(const int& playerXPosition, const int& playerYPosition);	//이동 함수
	void Die();		//죽는 함수
	void isHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower);	//맞으면실행

};



