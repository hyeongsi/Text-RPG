#include "Monster.h"

vector<Monster*>* Monster::monster = nullptr;
Pos* Monster::itemPosition = new Pos();

//각 자식몬스터에서 호출
void Monster::AddInstance()
{
	if (monster == nullptr)
		monster = new vector<Monster*>();
}

//모든몬스터 삭제
void Monster::ReleaseInstance()
{
	if (monster == nullptr)
		return;
	
	for (int i = 0; i < monster->size(); i++)
		delete (*monster)[i];

	monster->clear();

	delete monster;
	monster = nullptr;
}

//몬스터반환
vector<Monster*>* Monster::GetInstance()
{
	return monster;
}

//몬스터체력없으면 삭제
void Monster::Die()
{
	for (auto monsterHP = monster->begin(); monsterHP != monster->end();)
	{
		if ((*monsterHP)->GetHp() <= 0)
		{
			itemPosition->SetX(((*monsterHP)->GetPos().GetX() % 2 == 0) ? (*monsterHP)->GetPos().GetX() + 1 : (*monsterHP)->GetPos().GetX());
			itemPosition->SetY((*monsterHP)->GetPos().GetY());
			delete (*monsterHP);		//할당받은거 반납
			monster->erase(monsterHP);	//벡터에서 삭제
			return;
		}
		else
			monsterHP++;
	}
}

//몬스터스텟설정
void Monster::MonsterSetStats(const int& hp, const int& power, const int& speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

//몬스터 스텟외 정보들 설정
void Monster::Setting(const int& invincibilityTime, const int& bounceSize)
{
	this->invincibilityTime = invincibilityTime;
	this->bounceSize = bounceSize;
}