#include "Tank.h"

vector<Tank*>* Tank::tank = nullptr;
Pos* Tank::itemPosition = new Pos();
int Tank::exp = 0;

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
	if (tank == nullptr)
		return;

	for (int i = 0; i < tank->size(); i++)
		delete (*tank)[i];

	tank->clear();

	delete tank;
	tank = nullptr;
}

void Tank::SetStats(int hp, int power, int speed, int exp)
{
	Monster::MonsterSetStats(hp, power, speed);
	Tank::exp = exp;
}

void Tank::Move(int playerXPosition, int playerYPosition)
{
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
	for (auto tankHP = tank->begin(); tankHP != tank->end();)
	{
		if ((*tankHP)->Hp <= 0)
		{
			itemPosition->SetX(((*tankHP)->GetPos().GetX() % 2 == 0) ? (*tankHP)->GetPos().GetX() + 1 : (*tankHP)->GetPos().GetX());
			itemPosition->SetY((*tankHP)->GetPos().GetY());
			delete (*tankHP);		//할당받은거 반납
			tank->erase(tankHP);	//벡터에서 삭제
			return;
		}
		else
			tankHP++;
	}
}

void Tank::isHit(int playerXPosition, int playerYPosition, int playerDirection, int playerPower)
{
	int attackXPosition = 0;
	int attackYPosition = 0;

	int tankXPosition = this->GetPos().GetX();
	int tankYPosition = this->GetPos().GetY();

	if (playerDirection == RIGHT)
	{
		attackXPosition = playerXPosition + 3;
		attackYPosition = playerYPosition - 1;
	}
	else if (playerDirection == LEFT)
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
		if (playerDirection == RIGHT)
			this->SetPos(tankXPosition + bounceSize, tankYPosition);
		else if (playerDirection == LEFT)
			this->SetPos(tankXPosition - bounceSize, tankYPosition);
		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(invincibilityTime);
		isInvincibility = true;
		this->Hit(playerPower);
	}

	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}
