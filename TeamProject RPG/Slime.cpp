#include "Slime.h"

int Slime::exp = 0;
int Slime::itemDropPercentage = 0;

//객체추가
void Slime::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Slime());		//slime객체 추가
}   

//각 슬라임마다 체력과 공격력과 스피드 설정하기
void Slime::SetStats(int hp, int power, int speed, int exp, int itemDropPercentage)
{
	Monster::MonsterSetStats(hp, power, speed);
	Slime::exp = exp;
	Slime::itemDropPercentage = itemDropPercentage;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Slime::Move(const int& playerXPosition, const int& playerYPosition)
{
	if (this->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime(this->speed);
	}
	this->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 슬라임위치를 기준으로 슬라임이동방향을 결정
	this->SetPos((this->GetPos().GetX()-playerXPosition>0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY()- playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

//슬라임이 맞았을 때 실행할 함수
void Slime::IsHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower, const bool isAttack)
{
	if(isAttack == true)
		isAttacked = true;

	//타점
	int attackXPosition = 0;
	int attackYPosition = 0;

	//각 슬라임들의 위치
	int slimeXPosition = this->GetPos().GetX();
	int slimeYPosition = this->GetPos().GetY();

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
			if ((attackXPosition == slimeXPosition + y) && (attackYPosition == slimeYPosition - 2 + x))
			{
				isAttacked = true;
			}
		}
	}

	if (isAttacked == true && isInvincibility == false)
	{
		if (playerDirection == RIGHT)
			this->SetPos(slimeXPosition + bounceSize, slimeYPosition);

		else if (playerDirection == LEFT)
			this->SetPos(slimeXPosition - bounceSize, slimeYPosition);
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