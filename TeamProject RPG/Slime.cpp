#include "Slime.h"

vector<Slime*>* Slime::slime = nullptr;

void Slime::AddInstance()
{
	if (slime == nullptr)
		slime = new vector<Slime*>();
	slime->push_back(new Slime());		//slime��ü �߰�
}

vector<Slime*>* Slime::GetInstance()
{
	return slime;
}

void Slime::ReleaseInstance()
{
	//�����Ҵ������ϱ�
}

void Slime::SetStats(int hp, int power)
{
	this->Hp = hp;
	this->power = power;
}

void Slime::Move()
{
	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if (isMove)
	{
		delaymanager.SetStartTime();
		delaymanager.SetDelayTime(1000);
	}
	isMove = false;

	if (!delaymanager.CheckEndDelay())
		return;

	//������ �������ڸ� ĳ���Ͱ��ִ� ��ġ�� ��������ġ�� �������� �������̵������� ����
	//����1 �������� �ո���������
	//����2 �������� ��ġ�°�찡 ����
	for (int i = 0; i < slime->size(); i++)
	{
		(*slime)[i]->SetPos(((*slime)[i]->GetPos().GetX()-playerPosX>0) ? (*slime)[i]->GetPos().GetX() - 1 : (*slime)[i]->GetPos().GetX() + 1, ((*slime)[i]->GetPos().GetY()- playerPosY > 0) ? (*slime)[i]->GetPos().GetY() - 1 : (*slime)[i]->GetPos().GetY() + 1);
		isMove = true;
	}
}

void Slime::Die()
{
}