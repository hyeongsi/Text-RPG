#include "Slime.h"

vector<Slime*>* Slime::slime = nullptr;

//객체추가
void Slime::AddInstance()
{
	if (slime == nullptr)
		slime = new vector<Slime*>();
	slime->push_back(new Slime());		//slime객체 추가
}

//객체벡터반환
vector<Slime*>* Slime::GetInstance()
{
	return slime;
}

//동적할당해제하기
void Slime::ReleaseInstance()
{
	//동적할당해제하기
}

//각 슬라임마다 체력과 공격력과 스피드 설정하기
void Slime::SetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Slime::Move(int index)
{
	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if ((*slime)[index]->isMove)
	{
		delaymanager.SetStartTime();
		delaymanager.SetDelayTime((*slime)[index]->speed);
	}
	(*slime)[index]->isMove = false;

	if (!delaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 슬라임위치를 기준으로 슬라임이동방향을 결정
	(*slime)[index]->SetPos(((*slime)[index]->GetPos().GetX()-playerPosX>0) ? (*slime)[index]->GetPos().GetX() - 1 : (*slime)[index]->GetPos().GetX() + 1, ((*slime)[index]->GetPos().GetY()- playerPosY > 0) ? (*slime)[index]->GetPos().GetY() - 1 : (*slime)[index]->GetPos().GetY() + 1);
	(*slime)[index]->isMove = true;
}

void Slime::Move()
{
}

//이름 isDie변경생각
void Slime::Die()
{
	//슬라임체력없으면 삭제
	for (int i = 0; i < slime->size(); i++)
	{
		for (auto slimeHP = slime[i].begin(); slimeHP != slime[i].end(); i++)
		{
			if ((*slimeHP)->Hp <= 0)
				slime[i].erase(slimeHP);
		}
	}

}