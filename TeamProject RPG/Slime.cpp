#include "Slime.h"

vector<Slime*>* Slime::slime = nullptr;

void Slime::AddInstance()
{
	if (slime == nullptr)
		slime = new vector<Slime*>();
	slime->push_back(new Slime());		//slime객체 추가
}

vector<Slime*>* Slime::GetInstance()
{
	return slime;
}

void Slime::ReleaseInstance()
{
	//동적할당해제하기
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

	//간단히 설명하자면 캐릭터가있는 위치와 슬라임위치를 기준으로 슬라임이동방향을 결정
	//문제1 슬라임이 앞만보고있음
	//문제2 슬라임이 겹치는경우가 생김
	for (int i = 0; i < slime->size(); i++)
	{
		(*slime)[i]->SetPos(((*slime)[i]->GetPos().GetX()-playerPosX>0) ? (*slime)[i]->GetPos().GetX() - 1 : (*slime)[i]->GetPos().GetX() + 1, ((*slime)[i]->GetPos().GetY()- playerPosY > 0) ? (*slime)[i]->GetPos().GetY() - 1 : (*slime)[i]->GetPos().GetY() + 1);
		isMove = true;
	}
}

void Slime::Die()
{
}