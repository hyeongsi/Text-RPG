#include "Tank.h"

void Tank::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Tank());		//slime객체 추가
}

void Tank::SetStats(int hp, int power, int speed)
{
	Monster::MonsterSetStats(hp, power, speed);
}

void Tank::Move(const int& playerXPosition, const int& playerYPosition)
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

void Tank::IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower, const bool isAttack)
{
	if (isAttack == true)
		isAttacked = true;

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
