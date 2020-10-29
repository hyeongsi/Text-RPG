#include "Tank.h"

vector<Tank*>* Tank::tank = nullptr;
Pos* Tank::itemPosition = new Pos();

void Tank::AddInstance()
{
	if (tank == nullptr)
		tank = new vector<Tank*>();

	tank->push_back(new Tank());
}

vector<Tank*>* Tank::GetInstance()
{
	return tank;
}

void Tank::ReleaseInstance()
{
	//동적할당해제하기
}

void Tank::SetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

void Tank::Move()
{
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();

	if (this->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime(this->speed);
	}
	this->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	this->SetPos((this->GetPos().GetX() - playerXPosition > 0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY() - playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

void Tank::Die()
{
	for (auto tankHP = tank->begin(); tankHP != tank->end(); tankHP++)
	{
		if ((*tankHP)->Hp <= 0 && tankHP == --tank->end())		//벡터의 마지막에 있는놈은 특별대우.. 안하면 에러남 이유찾기
		{
			itemPosition->SetX(((*tankHP)->GetPos().GetX() % 2 == 0) ? (*tankHP)->GetPos().GetX() + 1 : (*tankHP)->GetPos().GetX());
			itemPosition->SetY((*tankHP)->GetPos().GetY());
			tank->pop_back();
			return;
		}
		else if ((*tankHP)->Hp <= 0)
		{
			itemPosition->SetX(((*tankHP)->GetPos().GetX() % 2 == 0) ? (*tankHP)->GetPos().GetX() + 1 : (*tankHP)->GetPos().GetX());
			itemPosition->SetY((*tankHP)->GetPos().GetY());
			tankHP = tank->erase(tankHP);
		}
	}
}

void Tank::isHit(int playerXPosition, int playerYPosition)
{
	int attackXPosition = 0;
	int attackYPosition = 0;

	int tankXPosition = this->GetPos().GetX();
	int tankYPosition = this->GetPos().GetY();

	if (player->GetDir() == RIGHT)
	{
		attackXPosition = playerXPosition + 3;
		attackYPosition = playerYPosition - 1;
	}
	else if (player->GetDir() == LEFT)
	{
		attackXPosition = playerXPosition - 5;
		attackYPosition = playerYPosition - 1;
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y >= -2; y--)
		{
			if ((attackXPosition == tankXPosition + y) && (attackYPosition == tankYPosition - 2 + x))
			{
				isAttacked = true;
			}
		}
	}

	if (isAttacked == true && isInvincibility == false)
	{
		if (player->GetDir() == RIGHT)
			this->SetPos(tankXPosition + rename, tankYPosition);
		else if (player->GetDir() == LEFT)
			this->SetPos(tankXPosition - rename, tankYPosition);
		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(invincibilityTime);
		isInvincibility = true;
		this->Hit(player->GetPower());
	}

	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}
