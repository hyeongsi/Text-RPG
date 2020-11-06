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

	void Move(const int& playerXPosition, const int& playerYPosition);	//�̵� �Լ�
	void Die();		//�״� �Լ�
	void isHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower);	//���������
};

