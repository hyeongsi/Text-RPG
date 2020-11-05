#pragma once
#include "Monster.h"

class Oak : public Monster
{
private:
	static vector<Oak*>* oak;
	Oak() {};

public:
	static void AddInstance();
	static vector<Oak*>* GetInstance();
	static void ReleaseInstance();

	//�����۹ڽ��� ��ǥ(������������ ��ǥ)
	static Pos* itemPosition;
	static int exp;

	void SetStats(int hp, int power, int speed, int exp);

	void Move(int playerXPosition, int playerYPosition);	//�̵� �Լ�
	void Die();		//�״� �Լ�
	void isHit(int playerXPosition, int playerYPosition, int playerDirection, int playerPower);	//���������
};

