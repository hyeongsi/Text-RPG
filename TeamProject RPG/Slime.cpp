#include "Slime.h"

vector<Slime*>* Slime::slime = nullptr;
Pos* Slime::itemPosition = new Pos();
int Slime::exp = 0;

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
	if (slime == nullptr)
		return;
	
	for (int i = 0; i < slime->size(); i++)
		delete (*slime)[i];

	slime->clear();

	delete slime;
	slime = nullptr;
}   

//각 슬라임마다 체력과 공격력과 스피드 설정하기
void Slime::SetStats(int hp, int power, int speed, int exp)
{
	Monster::MonsterSetStats(hp, power, speed);
	Slime::exp = exp;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Slime::Move(int playerXPosition, int playerYPosition)
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

//슬라임체력없으면 삭제
void Slime::Die()
{
	for (auto slimeHP = slime->begin(); slimeHP != slime->end();)
	{
		if ((*slimeHP)->Hp <= 0)
		{
			itemPosition->SetX(((*slimeHP)->GetPos().GetX() % 2 == 0) ? (*slimeHP)->GetPos().GetX() + 1 : (*slimeHP)->GetPos().GetX());
			itemPosition->SetY((*slimeHP)->GetPos().GetY());
			delete (*slimeHP);		//할당받은거 반납
			slime->erase(slimeHP);	//벡터에서 삭제
			return;
		}
		else
			slimeHP++;
	}
}

//슬라임이 맞았을 때 실행할 함수
void Slime::IsHit(int playerXPosition, int playerYPosition, int playerDirection, int playerPower)
{
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