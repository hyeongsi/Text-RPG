#pragma once

#include <Windows.h>
#include "Player.h"
#include "GameInfo.h"
//���⿡ ���͸� �ε�

class MapManager
{
private:
	string map[30][30] = {""};
	Pos playerPos;	//���ÿ� player pos

	//1����, 2����... 1���ʼ����ϸ� gameinfo���� 1���ʿ� ���� ������ ini���Ͽ��� �ҷ��ͼ�
	//�� �� ���Ͽ� �´� ���͸� new�� �����ؼ� �ش� ��ġ�� ��ġ.
	//�׷�����
	//gameinfo include, monster include...
	//player...�ε� 
	//���
	//Mapmanager���� player.getPos �� �Ŀ� �� ������ map�� �ְ� ���� ����� �Ŀ�
	//�ѹ��� playerPos�� �����ؼ� 9ĭ �׸��� �׸���.
public:
	void GoToXY(const int x,const int y);
	void PrintCharacter(Character* character);
	//void PrintCharacter(Monster monster);

	void CheckOutOfMap(); //�̰� ȣ�� �ϱ� ���� player.move�� ���� ������ �Ŀ�
	//üũ�ؼ� ���� = ����� �����ߴ�. �׷��� ��ġ�� ���� �� �� ���..?
};

enum MyEnum
{
	Player

};
