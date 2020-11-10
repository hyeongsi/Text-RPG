#include "Oak.h"

int Oak::exp = 0;
int Oak::itemDropPercentage = 0;

//객체추가
void Oak::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Oak());		//slime객체 추가
}


//각 오크마다 체력과 공격력과 스피드 설정하기
void Oak::SetStats(int hp, int power, int speed, int exp, int itemDropPercentage)
{
	Monster::MonsterSetStats(hp, power, speed);
	Oak::exp = exp;
	Oak::itemDropPercentage = itemDropPercentage;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Oak::Move(const int& playerXPosition, const int& playerYPosition)
{
	if (this->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime(this->speed);
	}
	this->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 오크위치를 기준으로 오크이동방향을 결정
	this->SetPos((this->GetPos().GetX() - playerXPosition > 0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY() - playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

//오크가 맞았을 때 실행할 함수
void Oak::IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower)
{
	//타점
	int attackXPosition = 0;
	int attackYPosition = 0;

	//각 오크들의 위치
	int oakXPosition = this->GetPos().GetX();
	int oakYPosition = this->GetPos().GetY();

	//플레이어보는방향에 따라서 공격위치설정
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
			if ((attackXPosition == oakXPosition + y) && (attackYPosition == oakYPosition - 2 + x))
			{
				isAttacked = true;
			}
		}
	}

	if (isAttacked == true && isInvincibility == false)
	{
		if (playerDirection == RIGHT)
			this->SetPos(oakXPosition + bounceSize, oakYPosition);

		else if (playerDirection == LEFT)
			this->SetPos(oakXPosition - bounceSize, oakYPosition);
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
