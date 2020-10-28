#pragma once
#include <vector>
#include "Character.h"
#include "Player.h"
#include "DelayManager.h"

class Oak : public Character
{
private:
	Player* player = Player::GetInstance();
	static vector<Oak*>* oak;
	DelayManager moveDelaymanager;
	DelayManager attackDelaymanager;
	bool isMove = true;			//�������ð��� �����̱����� ����� ����
	int speed = 1000;
	Oak() {};

	//���⿡�¾Ҵٸ�
	bool isAttacked = false;
	bool isInvincibility = false;	//�������¿���
	int invincibilityTime = 100;	//�����ð�
	int rename = 5;		//�¾����� �з��� ũ��? �̸��ٽ�����



public:
	static void AddInstance();
	static vector<Oak*>* GetInstance();
	static void ReleaseInstance();

	//�����۹ڽ��� ��ǥ(������������ ��ǥ)
	static Pos* itemPosition;

	void SetStats(int hp, int power, int speed);

	void Move();	//�̵� �Լ�
	void Die();		//�״� �Լ�
	void isHit(int playerXPosition, int playerYPosition);	//���������
};

